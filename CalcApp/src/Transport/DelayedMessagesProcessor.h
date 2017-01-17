#pragma once

#include <QList>

#include "MessageInfo.h"

namespace CalcApp
{

class DelayedMessagesProcessor
{
public:
    void AddDelayedMessage(MessageData const &data);
    bool CanDeliverMessage(MessageInfo const &prevMessage);
    MessageData DeliverMessage(MessageInfo const &prevMessage);

private:
    QList<MessageData>::ConstIterator FindMessageForDelivery(MessageInfo const &prevMessage);

    QList<MessageData> _delayedMessages;
};

}
