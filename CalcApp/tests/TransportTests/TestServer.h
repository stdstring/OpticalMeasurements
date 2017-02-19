#pragma once

#include <QList>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

#include <functional>

#include "ITransport.h"
#include "Message.h"

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
    std::function<void(ITransport*)> PreapartionAction;
    Message ExpectedMessage;
};

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    static void Check(ITransport *transport, QList<ClientEntry> const &entries);

private:
    ClientHandler(ITransport *transport, QThread *initThread, QList<ClientEntry> const &entries);

    ITransport *_transport;
    QThread *_initThread;
    QList<ClientEntry> _entries;

private slots:
    void ProcessStart();
    void ProcessFinish();
    void ProcessResponse(Message const &message);
    void ProcessData(Message const &message);
    void ProcessEvent(Message const &message);
};

}
