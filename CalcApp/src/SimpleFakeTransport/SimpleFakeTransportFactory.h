#pragma once

#include <QObject>

#include "../CommonLib/ITransportFactory.h"
#include "../CommonLib/TransportConfig.h"

namespace CalcApp
{

class SimpleFakeTransportFactory : public QObject, public ITransportFactory
{
public:
    SimpleFakeTransportFactory() {}

    virtual ITransport* Create(TransportConfig const &config, QObject *parent) override;
};

}
