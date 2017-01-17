#include <algorithm>
#include <functional>
#include <QList>
#include <stdexcept>

#include "MessageInfo.h"
#include "DelayedMessagesProcessor.h"

namespace CalcApp
{

void DelayedMessagesProcessor::AddDelayedMessage(MessageData const &data)
{
    _delayedMessages.append(data);
}

bool DelayedMessagesProcessor::CanDeliverMessage(MessageInfo const &prevMessage)
{
    QList<MessageData>::ConstIterator iterator = FindMessageForDelivery(prevMessage);
    return iterator != _delayedMessages.cend();
}

MessageData DelayedMessagesProcessor::DeliverMessage(MessageInfo const &prevMessage)
{
    QList<MessageData>::ConstIterator iterator = FindMessageForDelivery(prevMessage);
    if (iterator == _delayedMessages.cend())
        throw std::logic_error("Message for delivery is not found");
    return *iterator;
}

QList<MessageData>::ConstIterator DelayedMessagesProcessor::FindMessageForDelivery(MessageInfo const &prevMessage)
{
    std::function<bool(MessageData const &)> predicate = [&prevMessage](MessageData const &data)
    {
        return (prevMessage.GetPackageNumber() + 1) == data.first.GetPackageNumber();
    };
    return std::find_if(_delayedMessages.cbegin(), _delayedMessages.cend(), predicate);
}

}

