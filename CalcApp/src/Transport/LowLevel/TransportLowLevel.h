#pragma once

#include <QObject>

#include "ITransport.h"
#include "TcpTransport.h"
#include "UdpTransport.h"
#include "Message.h"
#include "TransportConfig.h"

namespace CalcApp
{

class TransportLowLevel : public ITransport
{
    Q_OBJECT
public:
    explicit TransportLowLevel(TransportConfig const &config, QObject *parent = nullptr);
    virtual void Connect() override;
    virtual void Send(Message const &message) override;

private:
    TcpTransport *_tcpTransport;
    UdpTransport *_udpTransport;
};

}
