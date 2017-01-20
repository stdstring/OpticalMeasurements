#include <QObject>

#include "ITransport.h"
#include "TcpTransport.h"
#include "UdpTransport.h"
#include "Message.h"
#include "TransportConfig.h"
#include "TransportLowLevel.h"

namespace CalcApp
{

TransportLowLevel::TransportLowLevel(TransportConfig const &config, QObject *parent) :
    ITransport(parent),
    _tcpTransport(new TcpTransport(config.TcpAddress, config.TcpPort, this)),
    _udpTransport(new UdpTransport(config.UdpPort, this))
{
    QObject::connect(_tcpTransport, &TcpTransport::ResponseReceived, this, &TransportLowLevel::ResponseReceived);
    QObject::connect(_tcpTransport, &TcpTransport::EventReceived, this, &TransportLowLevel::EventReceived);
    QObject::connect(_udpTransport, &UdpTransport::DataReceived, this, &TransportLowLevel::DataReceived);
}

void TransportLowLevel::Connect()
{
    _tcpTransport->Connect();
    _udpTransport->Connect();
}

void TransportLowLevel::Send(Message const &message)
{
    _tcpTransport->Send(message);
}

}