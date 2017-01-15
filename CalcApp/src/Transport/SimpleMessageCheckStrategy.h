#pragma once

#include <QList>
#include <QObject>

#include "IMessageCheckStrategy.h"
#include "MessageInfo.h"

namespace CalcApp
{

class SimpleMessageCheckStrategy : QObject, IMessageCheckStrategy
{
public:
    SimpleMessageCheckStrategy(int maxDelayedCount, QObject *parent);
    virtual bool Check(MessageInfo const &messages, QList<MessageData> const &delayedMessages) override;

private:
    int _maxDelayedCount;
};

}
