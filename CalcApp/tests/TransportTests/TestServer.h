#pragma once

#include <QList>
#include <QObject>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

#include "Message.h"
#include "TestServerConfig.h"

namespace CalcApp
{

class TestServer : public QObject
{
    Q_OBJECT
public:
    TestServer(TestServerConfig const &config, QList<Message> const &messages, QObject *parent = nullptr);

signals:
    void RequestReceived(Message const &message);

public slots:
    void Start();
    void Stop();

private:
    // TODO (std_string) : think about separation of tcp and udp parts
    TestServerConfig _config;
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

}
