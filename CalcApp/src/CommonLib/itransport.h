#pragma once

#include <QtPlugin>

#include "ControlMessage.h"
#include "DataMessage.h"

namespace CalcApp
{

class ITransport
{
public:
    // exchange
    virtual ControlMessage ProcessControlCmd(ControlMessage const &request) = 0;
    // events
    // TODO (std_string) : think about signals/slots for events
    virtual bool HasEvents() const = 0;
    virtual ControlMessage RetrieveEvent() = 0;
    // data
    // TODO (std_string) : think about signals/slots for data
    virtual bool HasData() const = 0;
    virtual DataMessage RetrieveData() = 0;
    virtual ~ITransport() { /* do nothing */ }
};

}

Q_DECLARE_INTERFACE(CalcApp::ITransport, "com.stdstring.CalcApp.ITransport")
