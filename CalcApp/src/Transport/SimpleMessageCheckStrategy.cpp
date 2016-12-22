#include <QList>
#include <QObject>

#include "IMessageCheckStrategy.h"
#include "MessageInfo.h"
#include "SimpleMessageCheckStrategy.h"

namespace CalcApp
{

SimpleMessageCheckStrategy::SimpleMessageCheckStrategy(int maxDelayedCount, QObject *parent) : QObject(parent), _maxDelayedCount(maxDelayedCount)
{
}

bool SimpleMessageCheckStrategy::Check(QList<MessageInfo> const &delayedMessages)
{
    return delayedMessages.size() <= _maxDelayedCount;
}

}

