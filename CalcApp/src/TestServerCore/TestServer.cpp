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

#include <stdexcept>

#include "Common/Message.h"
#include "Common/TransportSerialization.h"
#include "TestServer.h"
#include "TestServerConfig.h"

namespace CalcApp
{

namespace
{

void SendUdpData(QUdpSocket *socket, QString const &serverAddress, quint16 udpPortNumber, Message const &message)
{
    QByteArray buffer;
    QDataStream output(&buffer, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_5);
    TransportSerializer::Serialize(message, output);
    socket->writeDatagram(buffer, QHostAddress(serverAddress), udpPortNumber);
}

void SendTcpData(QTcpSocket *socket, Message const &message)
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

}

TestServer::TestServer(TestServerConfig const &config, QList<Message> const &messages, QObject *parent) :
    QObject(parent),
    _config(config),
    _messages(messages),
    _timer(nullptr),
    _server(nullptr),
    _tcpSocket(nullptr),
    _udpSocket(nullptr)
{
}

void TestServer::Start()
{
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
    if (_messages.first().GetType() == MessageType::DATA)
        SendUdpData(_udpSocket, _config.ServerAddress, _config.UdpPortNumber, _messages.takeFirst());
    else if (_messages.first().GetType() == MessageType::EVENT)
        SendTcpData(_tcpSocket, _messages.takeFirst());
    if (!_messages.isEmpty() && _messages.first().GetType() != MessageType::REQUEST)
        _timer->start();
}

void TestServer::TcpClientConnected()
{
    _tcpSocket = _server->nextPendingConnection();
    QObject::connect(_tcpSocket, &QTcpSocket::disconnected, this, &TestServer::TcpClientDisconnected);
    QObject::connect(_tcpSocket, &QTcpSocket::readyRead, this, &TestServer::ProcessClientRead);
    if (!_messages.isEmpty() && _messages.first().GetType() != MessageType::REQUEST)
        _timer->start();
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
        emit RequestReceived(Message(MessageType::REQUEST, data.second));
        // TODO (std_string) : use more functional approach
        if (_messages.isEmpty() || _messages.first().GetData() != data.second)
            SendTcpData(_tcpSocket, Message(MessageType::RESPONSE, QByteArray()));
        else
        {
            // remove request
            _messages.takeFirst();
            // send and remove response
            SendTcpData(_tcpSocket, _messages.takeFirst());
        }
        if (!_messages.isEmpty() && _messages.first().GetType() != MessageType::REQUEST)
            _timer->start();
    }
}

void TestServer::TcpClientDisconnected()
{
    QObject::disconnect(_tcpSocket, &QTcpSocket::disconnected, this, &TestServer::TcpClientDisconnected);
    QObject::disconnect(_tcpSocket, &QTcpSocket::readyRead, this, &TestServer::ProcessClientRead);
}

}
