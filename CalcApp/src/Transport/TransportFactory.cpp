#include <QObject>

#include "LowLevel/TransportLowLevel.h"
#include "IMessageCheckStrategy.h"
#include "ITransport.h"
#include "SimpleMessageCheckStrategy.h"
#include "Transport.h"
#include "TransportConfig.h"
#include "TransportFactory.h"

namespace CalcApp
{

TransportFactory::TransportFactory(QObject *parent) : QObject(parent)
{
}

ITransport* TransportFactory::Create(QObject *parent)
{
    // TODO (std_string) : implement working with config in future
    TransportConfig transportConfig(1, "127.0.0.1", 6666, 7777);
    ITransport *transportLowLevel = new TransportLowLevel(transportConfig, parent);
    IMessageCheckStrategy *messageCheckStrategy = new SimpleMessageCheckStrategy(transportConfig.MaxDelayedCount, parent);
    return new Transport(transportLowLevel, messageCheckStrategy, parent);
}

}
