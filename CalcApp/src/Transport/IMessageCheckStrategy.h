#pragma once

#include <QList>

#include "MessageInfo.h"

namespace CalcApp
{

class IMessageCheckStrategy
{
public:
    virtual bool Check(MessageInfo const &messages, QList<MessageData> const &delayedMessages) = 0;
};

}
