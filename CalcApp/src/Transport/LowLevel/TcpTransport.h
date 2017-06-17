#pragma once

#include <QObject>
#include <QString>
#include <QTcpSocket>

#include "Common/CommonDefs.h"
#include "Common/TransportConfig.h"
#include "Common/TransportSerialization.h"

namespace CalcApp
{

class TcpTransport : public QObject
{
    Q_OBJECT
public:
    TcpTransport(TransportConfig const &transportConfig, QObject *parent);
    void Connect();
    void Send(MessagePtr message);
    void Disconnect();

signals:
    void ResponseReceived(MessagePtr message);
    void EventReceived(MessagePtr message);

private:
    QString _address;
    quint16 _port;
    QTcpSocket *_socket;
    MessageHeader _messageHeader;

private slots:
    void ProcessRead();
};

}
