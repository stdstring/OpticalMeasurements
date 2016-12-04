#pragma once

#include "Message.h"
#include "MessageType.h"

namespace CalcApp
{

class ITransport
{
public:
    // request-response exchange
    virtual Message ProcessControlCmd(Message const &request) = 0;
    // retrieve data/events
    // TODO (std_string) : think about signals/slots for events
    virtual bool HasInput() const = 0;
    virtual Message RetrieveInput() = 0;
    virtual ~ITransport() { /* do nothing */ }
};

}
