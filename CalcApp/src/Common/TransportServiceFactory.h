#pragma once

#include <QObject>

#include "Common/ITransport.h"
#include "Common/ITransportFactory.h"
#include "Common/TransportConfig.h"


namespace CalcApp
{

class TransportServiceFactory : public ITransportFactory
{
public:
    explicit TransportServiceFactory(ITransportFactory *factory, QObject *parent = nullptr);

    virtual QString GetType() override;
    virtual ITransport* Create(TransportConfig const &transportConfig, QObject *parent) override;

private:
    ITransportFactory *_factory;
};

}
