#include <QByteArray>
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

#include <stdexcept>

#include "gtest/gtest.h"

#include "EqualityOperators.h"
#include "Message.h"
#include "TestServer.h"

namespace CalcApp
{

// TODO (std_string) : use data from config
const quint16 TcpPortNumber = 6666;
const quint16 UdpPortNumber = 7777;
const QString ServerAddress = "127.0.0.1";
const int TimerInterval = 400;

namespace
{

// TODO (std_string) : move into some common place

// format of all incoming/outgoing messages:
// tag (quint32) - probably added in future
// size (quint32)
// byte array

void SendUdpData(QUdpSocket *socket, Message const &message)
{
    QByteArray buffer;
    QDataStream output(&buffer, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_5);
    // tag (quint32) - probably added in future
    // size (quint32)
    output << static_cast<quint32>(message.GetData().size());
    // byte array
    output << message.GetData();
    socket->writeDatagram(buffer, QHostAddress(ServerAddress), UdpPortNumber);
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

TestServer::TestServer(QList<Message> const &messages, QObject *parent) :
    QObject(parent),
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
    _timer->setInterval(TimerInterval);
    _server = new QTcpServer(this);
    _udpSocket = new QUdpSocket(this);
    if (!_server->listen(QHostAddress(ServerAddress), TcpPortNumber))
    {
        throw std::logic_error("Listen error");
    }
    QObject::connect(_server, &QTcpServer::newConnection, this, &TestServer::TcpClientConnected);
    QObject::connect(_timer, &QTimer::timeout, this, &TestServer::ProcessTimeout);
}

void TestServer::Finish()
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
        SendUdpData(_udpSocket, _messages.takeFirst());
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

TestServerRunner::TestServerRunner(QList<Message> const &messages, QObject *parent) :
    QObject(parent),
    _server(new TestServer(messages, this)),
    _thread(new QThread(this))
{
    _server->moveToThread(_thread);
    QObject::connect(_thread, &QThread::started, _server, &TestServer::Start);
    QObject::connect(_thread, &QThread::finished, _server, &TestServer::Finish);

}

void TestServerRunner::Start()
{
    _thread->start();
}

void TestServerRunner::Stop()
{
    _thread->exit();
}

void ClientHandler::Check(ITransport *transport, QList<ClientEntry> const &entries)
{
    ClientHandler handler(transport, QThread::currentThread(), entries);
    QThread thread;
    transport->moveToThread(&thread);
    handler.moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, &handler, &ClientHandler::ProcessStart);
    QObject::connect(&thread, &QThread::finished, &handler, &ClientHandler::ProcessFinish);
    thread.start();
    EXPECT_TRUE(thread.wait());
}

ClientHandler::ClientHandler(ITransport *transport, QThread *initThread, QList<ClientEntry> const &entries) :
    QObject(nullptr),
    _transport(transport),
    _initThread(initThread),
    _entries(entries)
{
    QObject::connect(_transport, &ITransport::DataReceived, this, &ClientHandler::ProcessData);
    QObject::connect(_transport, &ITransport::EventReceived, this, &ClientHandler::ProcessEvent);
    QObject::connect(_transport, &ITransport::ResponseReceived, this, &ClientHandler::ProcessResponse);
}

void ClientHandler::ProcessStart()
{
    _entries.first().PreapartionAction(_transport);
}

void ClientHandler::ProcessFinish()
{
    _transport->moveToThread(_initThread);
    this->moveToThread(_initThread);
}

void ClientHandler::ProcessResponse(Message const &message)
{
    // TODO (std_string) : code duplication
    EXPECT_FALSE(_entries.isEmpty());
    EXPECT_EQ(_entries.takeFirst().ExpectedMessage ,message);
    if (_entries.isEmpty())
        QThread::currentThread()->exit();
    else
        _entries.first().PreapartionAction(_transport);
}

void ClientHandler::ProcessData(Message const &message)
{
    // TODO (std_string) : code duplication
    EXPECT_FALSE(_entries.isEmpty());
    EXPECT_EQ(_entries.takeFirst().ExpectedMessage ,message);
    if (_entries.isEmpty())
        QThread::currentThread()->exit();
    else
        _entries.first().PreapartionAction(_transport);
}

void ClientHandler::ProcessEvent(Message const &message)
{
    // TODO (std_string) : code duplication
    EXPECT_FALSE(_entries.isEmpty());
    EXPECT_EQ(_entries.takeFirst().ExpectedMessage ,message);
    if (_entries.isEmpty())
        QThread::currentThread()->exit();
    else
        _entries.first().PreapartionAction(_transport);
}

}
