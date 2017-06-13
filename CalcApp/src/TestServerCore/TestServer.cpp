#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QIODevice>
#include <QList>
#include <QPair>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

#include <memory>
#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Logger/ILogger.h"
#include "Common/Message.h"
#include "Common/TransportSerialization.h"
#include "TestServer.h"
#include "TestServerConfig.h"

namespace CalcApp
{

namespace
{

void SendUdpData(QUdpSocket *socket, QString const &serverAddress, quint16 udpPortNumber, MessagePtr message)
{
    QByteArray buffer;
    QDataStream output(&buffer, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_5);
    TransportSerializer::Serialize(message, output);
    socket->writeDatagram(buffer, QHostAddress(serverAddress), udpPortNumber);
}

void SendTcpData(QTcpSocket *socket, MessagePtr message)
{
    QByteArray buffer;
    QDataStream output(&buffer, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_5);
    TransportSerializer::Serialize(message, output);
    socket->write(buffer);
}

QPair<MessageHeader, QByteArray> StartReadTcpData(QTcpSocket *socket)
{
    if (socket->bytesAvailable() < TransportSerializer::GetMessageHeaderSize())
        return qMakePair(MessageHeader(), QByteArray());
    QDataStream input(socket);
    input.setVersion(QDataStream::Qt_5_5);
    MessageHeader header = TransportSerializer::DeserializeHeader(input);
    if (socket->bytesAvailable() < header.Size)
        return qMakePair(header, QByteArray());
    return qMakePair(header, TransportSerializer::DeserializeBody(header, input));
}

QByteArray ContinueReadTcpData(QTcpSocket *socket, MessageHeader const &header)
{
    if (socket->bytesAvailable() < header.Size)
        return QByteArray();
    QDataStream input(socket);
    input.setVersion(QDataStream::Qt_5_5);
    return TransportSerializer::DeserializeBody(header, input);
}

QPair<MessageHeader, QByteArray> ReadTcpData(QTcpSocket *socket, MessageHeader const &header)
{
    return header.Size == 0 ? StartReadTcpData(socket) : qMakePair(header, ContinueReadTcpData(socket, header));
}

void LogProcessedDataMessage(LoggerPtr logger, QByteArray const &messageData)
{
    // TODO (std_string) : move this into common place
    // 1) quint32 with package number
    // 2) quint32 with calculation number
    // 3) other data
    QDataStream stream(messageData);
    stream.setVersion(QDataStream::Qt_5_5);
    quint32 packageNumber, calcNumber;
    QByteArray messageBody;
    stream >> packageNumber >> calcNumber >> messageBody;
    QString infoTemplate("Processing DATA message with packageNumber = %1, calcNumber =%2, data = \"%3\"");
    logger.get()->WriteInfo(infoTemplate.arg(packageNumber).arg(calcNumber).arg(QString::fromUtf8(messageBody)));
}

void LogProcessedMessage(LoggerPtr logger, QString const &messageType, QByteArray const &messageData)
{
    logger.get()->WriteInfo(QString("Processing %1 message with data \"%2\"").arg(messageType).arg(QString::fromUtf8(messageData)));
}

}

TestServer::TestServer(TestServerConfig const &config, LoggerPtr logger, QList<MessagePtr> const &messages, QObject *parent) :
    QObject(parent),
    _config(config),
    _logger(logger),
    _messages(messages),
    _timer(nullptr),
    _server(nullptr),
    _tcpSocket(nullptr),
    _udpSocket(nullptr)
{
}

void TestServer::Start()
{
    _logger.get()->WriteInfo("Server started");
    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    _timer->setTimerType(Qt::TimerType::CoarseTimer);
    _timer->setInterval(_config.TimerInterval);
    _server = new QTcpServer(this);
    _udpSocket = new QUdpSocket(this);
    if (!_server->listen(QHostAddress(_config.ServerAddress), _config.TcpPortNumber))
    {
        throw std::logic_error("Listen error");
    }
    QObject::connect(_server, &QTcpServer::newConnection, this, &TestServer::TcpClientConnected);
    QObject::connect(_timer, &QTimer::timeout, this, &TestServer::ProcessTimeout);
}

void TestServer::Stop()
{
    _logger.get()->WriteInfo("Server stopped");
    _timer->stop();
    if (_tcpSocket != nullptr)
        _tcpSocket->close();
    _server->close();
    _udpSocket->close();
    delete _timer;
    delete _tcpSocket;
    delete _server;
    delete _udpSocket;
}

void TestServer::ProcessTimeout()
{
    // TODO (std_string) : use more functional approach
    if (_messages.first().get()->GetType() == MessageType::DATA)
    {
        LogProcessedDataMessage(_logger, _messages.first().get()->GetData());
        SendUdpData(_udpSocket, _config.ServerAddress, _config.UdpPortNumber, _messages.takeFirst());
    }
    else if (_messages.first().get()->GetType() == MessageType::EVENT)
    {
        LogProcessedMessage(_logger, "EVENT", _messages.first().get()->GetData());
        SendTcpData(_tcpSocket, _messages.takeFirst());
    }
    CheckAndStartTimer();
}

void TestServer::TcpClientConnected()
{
    _tcpSocket = _server->nextPendingConnection();
    QObject::connect(_tcpSocket, &QTcpSocket::disconnected, this, &TestServer::TcpClientDisconnected);
    QObject::connect(_tcpSocket, &QTcpSocket::readyRead, this, &TestServer::ProcessClientRead);
    CheckAndStartTimer();
}

void TestServer::ProcessClientRead()
{
    forever
    {
        QPair<MessageHeader, QByteArray> data = ReadTcpData(_tcpSocket, _tcpMessageHeader);
        if (data.second.isEmpty())
        {
            _tcpMessageHeader = data.first;
            return;
        }
        LogProcessedMessage(_logger, "REQUEST", data.second);
        emit RequestReceived(std::make_shared<Message>(MessageType::REQUEST, data.second));
        // TODO (std_string) : use more functional approach
        if (_messages.isEmpty() || _messages.first().get()->GetData() != data.second)
        {
            _logger.get()->WriteWarning("Unknown request");
            SendTcpData(_tcpSocket, std::make_shared<Message>(MessageType::RESPONSE, QByteArray()));
        }
        else
        {
            // remove request
            _messages.takeFirst();
            // send and remove response
            LogProcessedMessage(_logger, "RESPONSE", _messages.first().get()->GetData());
            SendTcpData(_tcpSocket, _messages.takeFirst());
        }
        CheckAndStartTimer();
    }
}

void TestServer::TcpClientDisconnected()
{
    QObject::disconnect(_tcpSocket, &QTcpSocket::disconnected, this, &TestServer::TcpClientDisconnected);
    QObject::disconnect(_tcpSocket, &QTcpSocket::readyRead, this, &TestServer::ProcessClientRead);
}

void TestServer::CheckAndStartTimer()
{
    if (_messages.isEmpty())
        _logger.get()->WriteInfo("All messages are processed");
    else if (_messages.first().get()->GetType() != MessageType::REQUEST)
        _timer->start();
}

}
