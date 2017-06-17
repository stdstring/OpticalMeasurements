#pragma once

#include <QObject>

#include "Common/CommonDefs.h"
#include "Common/ITransport.h"
#include "Common/TransportConfig.h"
#include "TcpTransport.h"
#include "UdpTransport.h"

namespace CalcApp
{

class TransportLowLevel : public ITransport
{
    Q_OBJECT
public:
    explicit TransportLowLevel(TransportConfig const &config, QObject *parent = nullptr);
    virtual void Connect() override;
    virtual void Send(MessagePtr message) override;
    virtual void Disconnect() override;

private:
    TcpTransport *_tcpTransport;
    UdpTransport *_udpTransport;
};

}
