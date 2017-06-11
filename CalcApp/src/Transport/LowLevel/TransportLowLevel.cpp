#include <QObject>

#include "Common/CommonDefs.h"
#include "Common/ITransport.h"
#include "Common/Message.h"
#include "Common/TransportConfig.h"
#include "TcpTransport.h"
#include "TransportLowLevel.h"
#include "UdpTransport.h"

namespace CalcApp
{

TransportLowLevel::TransportLowLevel(TransportConfig const &config, QObject *parent) :
    ITransport(parent),
    _tcpTransport(new TcpTransport(config, this)),
    _udpTransport(new UdpTransport(config, this))
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

void TransportLowLevel::Send(MessagePtr message)
{
    _tcpTransport->Send(message);
}

}
