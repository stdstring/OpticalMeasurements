#include <QObject>

#include "../CommonLib/ITransportFactory.h"
#include "../CommonLib/TransportConfig.h"
#include "SimpleFakeTransport.h"
#include "SimpleFakeTransportFactory.h"

namespace CalcApp
{

ITransport* SimpleFakeTransportFactory::Create(TransportConfig const &config, QObject *parent)
{
    return new SimpleFakeTransport(config, parent);
}

}
