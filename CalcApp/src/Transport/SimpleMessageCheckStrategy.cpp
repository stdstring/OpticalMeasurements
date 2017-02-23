#include <QList>
#include <QObject>
#include <QtGlobal>

#include "IMessageCheckStrategy.h"
#include "MessageInfo.h"
#include "SimpleMessageCheckStrategy.h"

namespace CalcApp
{

SimpleMessageCheckStrategy::SimpleMessageCheckStrategy(quint32 maxDelayedCount, QObject *parent) :
    IMessageCheckStrategy(parent),
    _maxDelayedCount(maxDelayedCount)
{
}

bool SimpleMessageCheckStrategy::Check(MessageInfo const &message, QList<MessageData> const &delayedMessages)
{
    Q_UNUSED(message);
    return delayedMessages.size() < _maxDelayedCount;
}

}

