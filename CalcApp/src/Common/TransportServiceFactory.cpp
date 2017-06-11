#include <QObject>

#include "Common/ITransport.h"
#include "Common/ITransportFactory.h"
#include "Common/TransportConfig.h"
#include "TransportService.h"
#include "TransportServiceFactory.h"

namespace CalcApp
{

TransportServiceFactory::TransportServiceFactory(ITransportFactory *factory, QObject *parent) :
    ITransportFactory(parent),
    _factory(factory)
{
}

ITransport* TransportServiceFactory::Create(TransportConfig const &transportConfig, QObject *parent)
{
    return new TransportService(_factory, transportConfig, parent);
}

}
