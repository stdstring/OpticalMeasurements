#pragma once

#include <QtPlugin>

#include "Message.h"

namespace CalcApp
{

class ITransport
{
public:
    virtual Message ProcessControlCmd(Message const &request) = 0;
    virtual bool HasData() const = 0;
    virtual Message RetrieveData() = 0;
    virtual ~ITransport() { /* do nothing */ }
};

}

Q_DECLARE_INTERFACE(CalcApp::ITransport, "com.stdstring.CalcApp.ITransport")
