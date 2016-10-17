#pragma once

#include <cstddef>
#include "Message.h"

namespace CalcApp
{

class ITransport
{
public:
    virtual Message ProcessControlCmd(Message const &request) = 0;
    virtual bool HasData() const = 0;
    virtual Message RetrieveData() = 0;
};

}
