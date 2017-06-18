#include "CommonDefs.h"
#include "ITransportFactory.h"
#include "Lazy.h"
#include "TransportConfig.h"
#include "ExecutionState.h"

namespace CalcApp
{

ExecutionState::ExecutionState(ITransportFactory *transportFactory, TransportConfig const &transportConfig) :
    _transport([transportFactory, transportConfig](){ return TransportPtr(transportFactory->Create(transportConfig, nullptr)); })
{
}

bool ExecutionState::HasTransport() const
{
    return _transport.HasValue();
}

TransportPtr ExecutionState::GetTransport()
{
    return _transport.GetValue();
}

}
