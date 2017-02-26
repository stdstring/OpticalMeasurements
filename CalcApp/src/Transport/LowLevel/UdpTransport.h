#pragma once

#include <QObject>
#include <QUdpSocket>

#include "Common/Message.h"

namespace CalcApp
{

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

}
