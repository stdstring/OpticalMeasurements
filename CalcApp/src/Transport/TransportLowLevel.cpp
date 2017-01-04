#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QUdpSocket>

#include "Message.h"
#include "TransportLowLevel.h"

namespace CalcApp
{

TransportConfig::TransportConfig(QString const &tcpAddress, quint16 tcpPort, quint16 udpPort) :
    TcpAddress(tcpAddress),
    TcpPort(tcpPort),
    UdpPort(udpPort)
{
}

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

TransportLowLevel::TransportLowLevel(TransportConfig const &config, QObject *parent) : TransportLowLevelBase(parent)
{
}

void TransportLowLevel::Connect()
{
}

Message TransportLowLevel::Exchange(Message const &message)
{
}

}
