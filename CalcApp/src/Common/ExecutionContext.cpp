#include "CommonDefs.h"
#include "ITransportFactory.h"
#include "Lazy.h"
#include "TransportConfig.h"
#include "ExecutionContext.h"

namespace CalcApp
{

ExecutionContext::ExecutionContext(ITransportFactory *transportFactory, TransportConfig const &transportConfig) :
    _transport([transportFactory, transportConfig](){ return TransportPtr(transportFactory->Create(transportConfig, nullptr)); })
{
}

bool ExecutionContext::HasTransport() const
{
    return _transport.HasValue();
}

TransportPtr ExecutionContext::GetTransport()
{
    return _transport.GetValue();
}

}
