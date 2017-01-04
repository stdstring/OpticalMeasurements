#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QUdpSocket>

#include "Message.h"
#include "TransportLowLevel.h"

namespace CalcApp
{

TcpTransport::TcpTransport(QString const &address, quint16 port, QObject *parent)
{
}

void TcpTransport::Connect()
{
}

Message TcpTransport::Exchange(Message const &message)
{
}

UdpTransport::UdpTransport(quint16 port, QObject *parent)
{
}

void UdpTransport::Connect()
{
}

TransportLowLevel::TransportLowLevel(QObject *parent) : TransportLowLevelBase(parent)
{
}

Message TransportLowLevel::Exchange(Message const &message)
{
}

}
