#pragma once

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QUdpSocket>

#include "Message.h"
#include "TransportLowLevelBase.h"

namespace CalcApp
{

class TcpTransport : public QObject
{
    Q_OBJECT
public:
    TcpTransport(QString const &address, quint16 port, QObject *parent);
    void Connect();
    Message Exchange(Message const &message);

signals:
    void EventReceived(Message const &message);

private:
    QString _address;
    quint16 _port;
    QTcpSocket *_socket;
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
};

class TransportLowLevel : public TransportLowLevelBase
{
    Q_OBJECT
public:
    explicit TransportLowLevel(QObject *parent);
    virtual Message Exchange(Message const &message) override;
};

}
