#pragma once

#include "CommonDefs.h"
#include "ITransportFactory.h"
#include "Lazy.h"

namespace CalcApp
{

class ExecutionState
{
public:
    ExecutionState(ITransportFactory *transportFactory, TransportConfig const &transportConfig);

    // access to transport
    bool HasTransport() const;
    TransportPtr GetTransport();

    ExecutionState() = delete;
    ExecutionState(ExecutionState const&) = delete;
    ExecutionState(ExecutionState&&) = delete;
    ExecutionState& operator=(ExecutionState const&) = delete;
    ExecutionState& operator=(ExecutionState&&) = delete;

private:
    Lazy<TransportPtr> _transport;
};

}
