#pragma once

#include <QObject>
#include <QUdpSocket>

#include "Common/CommonDefs.h"
#include "Common/TransportConfig.h"

namespace CalcApp
{

class UdpTransport : public QObject
{
    Q_OBJECT
public:
    UdpTransport(TransportConfig const &transportConfig, QObject *parent);
    void Connect();

signals:
    void DataReceived(MessagePtr message);

private:
    quint16 _port;
    QUdpSocket *_socket;

private slots:
    void ProcessRead();
};

}
