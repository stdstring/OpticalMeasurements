#pragma once

#include <QList>

#include "IMessageCheckStrategy.h"
#include "MessageInfo.h"
#include "Message.h"

namespace CalcApp
{

class DelayedMessagesProcessor
{
public:
    DelayedMessagesProcessor(IMessageCheckStrategy *messageCheckStrategy);
    void AddDelayedMessage(MessageInfo const &info, Message const &message);
    bool CanDeliverMessage(MessageInfo const &prevMessage);
    MessageData DeliverMessage(MessageInfo const &prevMessage);

private:
    QList<MessageData> _delayedMessages;
    IMessageCheckStrategy *_messageCheckStrategy;
};

}
