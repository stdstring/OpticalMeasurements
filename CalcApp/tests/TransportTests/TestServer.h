#pragma once

#include <QList>
#include <QObject>
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

class TestServer : public QObject
{
    Q_OBJECT
public:
    TestServer(QList<Message> const &messages, QObject *parent = nullptr);

signals:
    void RequestReceived(Message const &message);

public slots:
    void Start();
    void Finish();

private:
    // TODO (std_string) : think about separation of tcp and udp parts
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
    TestServerRunner(QList<Message> const &messages, QObject *parent = nullptr);
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
