#pragma once

#include <QObject>

#include "TransportLowLevelBase.h"

namespace CalcApp
{

class TcpTransport
{
};

class UdpTransport
{
};

class TransportLowLevel : public TransportLowLevelBase
{
    Q_OBJECT
public:
    explicit TransportLowLevel(QObject *parent);
};

}
