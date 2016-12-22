#pragma once

#include <QList>

#include "MessageInfo.h"

namespace CalcApp
{

class IMessageCheckStrategy
{
public:
    virtual bool Check(QList<MessageInfo> const &delayedMessages) = 0;
};

}
