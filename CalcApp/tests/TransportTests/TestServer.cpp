#include <QByteArray>
#include <QCoreApplication>
#include <QDataStream>
#include <QHostAddress>
#include <QIODevice>
#include <QList>
#include <QPair>
#include <QString>
#include <Qt>
#include <QThread>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

#include <memory>
#include <stdexcept>

#include "gtest/gtest.h"

#include "LowLevel/TransportLowLevel.h"
#include "EqualityOperators.h"
#include "IMessageCheckStrategy.h"
#include "ITransport.h"
#include "Message.h"
#include "SimpleMessageCheckStrategy.h"
#include "Transport.h"
#include "TransportConfig.h"
#include "TestServer.h"

namespace CalcApp
{

namespace
{

// TODO (std_string) : move into some common place

// format of all incoming/outgoing messages:
// tag (quint32) - probably added in future
// size (quint32)
// byte array

void SendUdpData(QUdpSocket *socket, QString const &serverAddress, quint16 udpPortNumber, Message const &message)
{
    QByteArray buffer;
    QDataStream output(&buffer, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_5);
    // tag (quint32) - probably added in future
    // size (quint32)
    output << static_cast<quint32>(message.GetData().size());
    // byte array
    output << message.GetData();
    socket->writeDatagram(buffer, QHostAddress(serverAddress), udpPortNumber);
}

void SendTcpData(QTcpSocket *socket, Message const &message)
{
    QByteArray buffer;
    QDataStream output(&buffer, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_5);
    // tag (quint32) - probably added in future
    // size (quint32)
    output << static_cast<quint32>(message.GetData().size());
    // byte array
    output << message.GetData();
    socket->write(buffer);
}

QPair<quint32, QByteArray> StartReadTcpData(QTcpSocket *socket)
{
    // tag (quint32) - probably added in future
    // size (quint32)
    if (socket->bytesAvailable() < sizeof(quint32))
        return qMakePair(0, QByteArray());
    QDataStream input(socket);
    quint32 size = 0;
    input >> size;
    if (socket->bytesAvailable() < size)
        return qMakePair(size, QByteArray());
    // byte array
    QByteArray data;
    input >> data;
    return qMakePair(size, data);
}

QByteArray ContinueReadTcpData(QTcpSocket *socket, quint32 size)
{
    if (socket->bytesAvailable() < size)
        return QByteArray();
    // byte array
    QByteArray data;
    QDataStream input(socket);
    input >> data;
    return data;
}

QPair<quint32, QByteArray> ReadTcpData(QTcpSocket *socket, quint32 size)
{
    return size == 0 ? StartReadTcpData(socket) : qMakePair(size, ContinueReadTcpData(socket, size));
}

}

TestServerConfig::TestServerConfig(int timerInterval, QString const &serverAddress, quint16 tcpPortNumber, quint16 udpPortNumber) :
    TimerInterval(timerInterval),
    ServerAddress(serverAddress),
    TcpPortNumber(tcpPortNumber),
    UdpPortNumber(udpPortNumber)
{
}

TestServer::TestServer(TestServerConfig const &config, QList<Message> const &messages, QObject *parent) :
    QObject(parent),
    _config(config),
    _messages(messages),
    _timer(nullptr),
    _server(nullptr),
    _tcpSocket(nullptr),
    _tcpMessageSize(0),
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
    if (!_messages.isEmpty() && _messages.first().GetType() != MessageType::RESPONSE)
        _timer->start();
}

void TestServer::TcpClientConnected()
{
    _tcpSocket = _server->nextPendingConnection();
    QObject::connect(_tcpSocket, &QTcpSocket::disconnected, this, &TestServer::TcpClientDisconnected);
    QObject::connect(_tcpSocket, &QTcpSocket::readyRead, this, &TestServer::ProcessClientRead);
    if (!_messages.isEmpty() && _messages.first().GetType() != MessageType::RESPONSE)
        _timer->start();
}

void TestServer::ProcessClientRead()
{
    forever
    {
        QPair<quint16, QByteArray> data = ReadTcpData(_tcpSocket, _tcpMessageSize);
        if (data.second.isEmpty())
        {
            _tcpMessageSize = data.first;
            return;
        }
        emit RequestReceived(Message(MessageType::REQUEST, data.second));
        // TODO (std_string) : use more functional approach
        if (!_messages.isEmpty() && _messages.first().GetType() == MessageType::RESPONSE)
            SendTcpData(_tcpSocket, _messages.takeFirst());
        else
            SendTcpData(_tcpSocket, Message(MessageType::RESPONSE, QByteArray()));
        if (!_messages.isEmpty() && _messages.first().GetType() != MessageType::RESPONSE)
            _timer->start();
    }
}

void TestServer::TcpClientDisconnected()
{
    QObject::disconnect(_tcpSocket, &QTcpSocket::disconnected, this, &TestServer::TcpClientDisconnected);
    QObject::disconnect(_tcpSocket, &QTcpSocket::readyRead, this, &TestServer::ProcessClientRead);
}

TestServerRunner::TestServerRunner(TestServerConfig const &config, QObject *parent) :
    QObject(parent),
    _config(config),
    _thread(new QThread(this))
{
}

void TestServerRunner::Start(const QList<Message> &messages)
{
    _server.reset(new TestServer(_config, messages, nullptr));
    _server.get()->moveToThread(_thread);
    QObject::connect(_thread, &QThread::started, _server.get(), &TestServer::Start);
    QObject::connect(_thread, &QThread::finished, _server.get(), &TestServer::Stop);
    _thread->start();
}

void TestServerRunner::Stop()
{
    _thread->exit();
    _thread->wait();
    QObject::disconnect(_thread, &QThread::started, _server.get(), &TestServer::Start);
    QObject::disconnect(_thread, &QThread::finished, _server.get(), &TestServer::Stop);
    _server.reset();
}

ClientEntry::ClientEntry(Message const &incomingMessage) :
    ClientEntry(std::shared_ptr<Message>(), incomingMessage)
{
}

ClientEntry::ClientEntry(std::shared_ptr<Message> outgoingMessage, Message const &incomingMessage) :
    OutgoingMessage(outgoingMessage),
    IncomingMessage(incomingMessage)
{
}

namespace
{

void SendOutgoingMessage(ITransport *transport, ClientEntry const &entry)
{
    if (entry.OutgoingMessage)
        transport->Send(*entry.OutgoingMessage.get());
}

}

void ClientHandler::Check(TransportConfig const &config, QList<ClientEntry> const &entries)
{
    int argc = 0;
    QCoreApplication app(argc, {});
    Q_UNUSED(app);
    ClientHandler handler(config, QThread::currentThread(), entries);
    QThread thread;
    handler.moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, &handler, &ClientHandler::ProcessStart);
    QObject::connect(&thread, &QThread::finished, &handler, &ClientHandler::ProcessFinish);
    thread.start();
    EXPECT_TRUE(thread.wait());
}

ClientHandler::ClientHandler(TransportConfig const &config, QThread *initThread, QList<ClientEntry> const &entries) :
    QObject(nullptr),
    _config(config),
    _transport(nullptr),
    _initThread(initThread),
    _entries(entries)
{
}

void ClientHandler::ProcessStart()
{
    ITransport *transportLowLevel = new TransportLowLevel(_config, this);
    IMessageCheckStrategy *messageCheckStrategy = new SimpleMessageCheckStrategy(_config.MaxDelayedCount, this);
    _transport = new Transport(transportLowLevel, messageCheckStrategy, this);
    QObject::connect(_transport, &ITransport::DataReceived, this, &ClientHandler::ProcessMessage);
    QObject::connect(_transport, &ITransport::EventReceived, this, &ClientHandler::ProcessMessage);
    QObject::connect(_transport, &ITransport::ResponseReceived, this, &ClientHandler::ProcessMessage);
    _transport->Connect();
    SendOutgoingMessage(_transport, _entries.first());
}

void ClientHandler::ProcessFinish()
{
    if (_transport != nullptr)
        delete _transport;
    _transport = nullptr;
    this->moveToThread(_initThread);
}

void ClientHandler::ProcessMessage(Message const &message)
{
    EXPECT_FALSE(_entries.isEmpty());
    EXPECT_EQ(_entries.takeFirst().IncomingMessage ,message);
    if (_entries.isEmpty())
        QThread::currentThread()->exit();
    else
        SendOutgoingMessage(_transport, _entries.first());
}

}
