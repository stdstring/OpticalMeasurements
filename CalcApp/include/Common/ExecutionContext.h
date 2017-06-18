#pragma once

#include "CommonDefs.h"
#include "ITransportFactory.h"
#include "Lazy.h"

namespace CalcApp
{

class ExecutionContext
{
public:
    ExecutionContext(ITransportFactory *transportFactory, TransportConfig const &transportConfig);

    // access to transport
    bool HasTransport() const;
    TransportPtr GetTransport();

    ExecutionContext() = delete;
    ExecutionContext(ExecutionContext const&) = delete;
    ExecutionContext(ExecutionContext&&) = delete;
    ExecutionContext& operator=(ExecutionContext const&) = delete;
    ExecutionContext& operator=(ExecutionContext&&) = delete;

private:
    Lazy<TransportPtr> _transport;
};

}
