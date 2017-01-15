#pragma once

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QUdpSocket>

#include "Message.h"
#include "TransportLowLevelBase.h"

namespace CalcApp
{

struct TransportConfig
{
public:
    TransportConfig(QString const &tcpAddress, quint16 tcpPort, quint16 udpPort);

    QString TcpAddress;
    quint16 TcpPort;
    quint16 UdpPort;
};

enum TcpTransportState { WAITING_EVENT, WAITING_RESPONSE };

class TcpTransport : public QObject
{
    Q_OBJECT
public:
    TcpTransport(QString const &address, quint16 port, QObject *parent);
    void Connect();
    void Send(Message const &message);

signals:
    void ResponseReceived(Message const &message);
    void EventReceived(Message const &message);

private:
    QString _address;
    quint16 _port;
    QTcpSocket *_socket;
    quint32 _messageSize;
    TcpTransportState _state;

private slots:
    void ProcessRead();
};

class UdpTransport : public QObject
{
    Q_OBJECT
public:
    UdpTransport(quint16 port, QObject *parent);
    void Connect();

signals:
    void DataReceived(Message const &message);

private:
    quint16 _port;
    QUdpSocket *_socket;

private slots:
    void ProcessRead();
};

class TransportLowLevel : public TransportLowLevelBase
{
    Q_OBJECT
public:
    explicit TransportLowLevel(TransportConfig const &config, QObject *parent);
    virtual void Connect() override;
    virtual void Send(Message const &message) override;

private:
    TcpTransport *_tcpTransport;
    UdpTransport *_udpTransport;
};

}
