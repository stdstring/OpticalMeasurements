#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QThread>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

#include <memory>

#include "ITransport.h"
#include "Message.h"
#include "TransportConfig.h"

namespace CalcApp
{

struct TestServerConfig
{
public:
    TestServerConfig(int timerInterval, QString const &serverAddress, quint16 tcpPortNumber, quint16 udpPortNumber);

    int TimerInterval;
    QString ServerAddress;
    quint16 TcpPortNumber;
    quint16 UdpPortNumber;
};

class TestServer : public QObject
{
    Q_OBJECT
public:
    TestServer(TestServerConfig const &config, QList<Message> const &messages, QObject *parent = nullptr);

signals:
    void RequestReceived(Message const &message);

public slots:
    void Start();
    void Finish();

private:
    // TODO (std_string) : think about separation of tcp and udp parts
    TestServerConfig const &_config;
    QList<Message> _messages;
    QTimer *_timer;
    QTcpServer *_server;
    QTcpSocket *_tcpSocket;
    quint32 _tcpMessageSize;
    QUdpSocket *_udpSocket;

private slots:
    void ProcessTimeout();
    void TcpClientConnected();
    void ProcessClientRead();
    void TcpClientDisconnected();
};

class TestServerRunner : public QObject
{
    Q_OBJECT
public:
    TestServerRunner(TestServerConfig const &config, QList<Message> const &messages, QObject *parent = nullptr);
    void Start();
    void Stop();

private:
    TestServer *_server;
    QThread *_thread;
};

struct ClientEntry
{
public:
    ClientEntry(Message const &incomingMessage);
    ClientEntry(std::shared_ptr<Message> outgoingMessage, Message const &incomingMessage);

    std::shared_ptr<Message> OutgoingMessage;
    Message IncomingMessage;
};

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    static void Check(TransportConfig const &config, QList<ClientEntry> const &entries);

private:
    ClientHandler(TransportConfig const &config, QThread *initThread, QList<ClientEntry> const &entries);

    TransportConfig _config;
    ITransport *_transport;
    QThread *_initThread;
    QList<ClientEntry> _entries;

private slots:
    void ProcessStart();
    void ProcessFinish();
    void ProcessMessage(Message const &message);
};

}
