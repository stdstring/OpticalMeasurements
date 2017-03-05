#pragma once

#include <QObject>
#include <QString>
#include <QTcpSocket>

#include "Common/Message.h"
#include "Common/TransportConfig.h"

namespace CalcApp
{

enum TcpTransportState { WAITING_EVENT, WAITING_RESPONSE };

class TcpTransport : public QObject
{
    Q_OBJECT
public:
    TcpTransport(TransportConfig const &transportConfig, QObject *parent);
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

}
