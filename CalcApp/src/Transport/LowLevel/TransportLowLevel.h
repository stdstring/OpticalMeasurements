#pragma once

#include <QObject>

#include "TcpTransport.h"
#include "UdpTransport.h"
#include "Message.h"
#include "TransportConfig.h"
#include "TransportLowLevelBase.h"

namespace CalcApp
{

class TransportLowLevel : public TransportLowLevelBase
{
    Q_OBJECT
public:
    explicit TransportLowLevel(TransportConfig const &config, QObject *parent);
    virtual void Connect() override;
    virtual void Send(Message const &message) override;

private:
    TcpTransport *_tcpTransport;
    UdpTransport *_udpTransport;
};

}
