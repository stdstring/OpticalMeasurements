#include <QObject>

#include "Common/ITransport.h"
#include "Common/ITransportFactory.h"
#include "Common/TransportConfig.h"
#include "LowLevel/TransportLowLevel.h"
#include "IMessageCheckStrategy.h"
#include "SimpleMessageCheckStrategy.h"
#include "Transport.h"
#include "TransportFactory.h"

namespace CalcApp
{

TransportFactory::TransportFactory(QObject *parent) : ITransportFactory(parent)
{
}

ITransport* TransportFactory::Create(const TransportConfig &transportConfig, QObject *parent)
{
    ITransport *transportLowLevel = new TransportLowLevel(transportConfig, parent);
    IMessageCheckStrategy *messageCheckStrategy = new SimpleMessageCheckStrategy(transportConfig.MaxDelayedCount, parent);
    ITransport *transport = new Transport(transportLowLevel, messageCheckStrategy, parent);
    transportLowLevel->setParent(transport);
    messageCheckStrategy->setParent(transport);
    return transport;
}

}
