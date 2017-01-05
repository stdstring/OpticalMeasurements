#include <QHostAddress>
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

TcpTransport::TcpTransport(QString const &address, quint16 port, QObject *parent) :
    QObject(parent),
    _address(address),
    _port(port),
    _socket(new QTcpSocket(this))
{
}

void TcpTransport::Connect()
{
    _socket->connectToHost(QHostAddress(_address), _port);
}

Message TcpTransport::Exchange(Message const &message)
{
}

UdpTransport::UdpTransport(quint16 port, QObject *parent) :
    QObject(parent),
    _port(port),
    _socket(new QUdpSocket(this))
{
}

void UdpTransport::Connect()
{
    _socket->bind(_port);
}

TransportLowLevel::TransportLowLevel(TransportConfig const &config, QObject *parent) :
    TransportLowLevelBase(parent),
    _tcpTransport(new TcpTransport(config.TcpAddress, config.TcpPort, this)),
    _udpTransport(new UdpTransport(config.UdpPort, this))
{
}

void TransportLowLevel::Connect()
{
    _tcpTransport->Connect();
    _udpTransport->Connect();
}

Message TransportLowLevel::Exchange(Message const &message)
{
    return _tcpTransport->Exchange(message);
}

}
