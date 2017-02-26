#pragma once

#include <QObject>

#include "Common/ITransport.h"
#include "Common/Message.h"
#include "TcpTransport.h"
#include "TransportConfig.h"
#include "UdpTransport.h"

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
