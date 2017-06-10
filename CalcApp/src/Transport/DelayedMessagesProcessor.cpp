#include <QObject>
#include <QList>

#include <algorithm>
#include <functional>
#include <stdexcept>

#include "MessageInfo.h"
#include "DelayedMessagesProcessor.h"

namespace CalcApp
{

namespace
{

QList<MessageData>::Iterator FindMessage(QList<MessageData> &storage, quint32 packageNumber)
{
    std::function<bool(MessageData&)> predicate = [packageNumber](MessageData &data)
    {
        return data.first.GetPackageNumber() == packageNumber;
    };
    return std::find_if(storage.begin(), storage.end(), predicate);
}

}

DelayedMessagesProcessor::DelayedMessagesProcessor(IMessageCheckStrategy *messageCheckStrategy, QObject *parent) :
    QObject(parent),
    _messageCheckStrategy(messageCheckStrategy)
{
}

void DelayedMessagesProcessor::AddDelayedMessage(MessageInfo const &info, Message const &message)
{
    if (FindMessage(_delayedMessages, info.GetPackageNumber()) != _delayedMessages.end())
        return;
    if (_messageCheckStrategy->Check(info, _delayedMessages))
        _delayedMessages.append(MessageData(info, message));
    else
        emit MessageProcessFail();
}

bool DelayedMessagesProcessor::CanDeliverMessage(MessageInfo const &prevMessage)
{
    QList<MessageData>::Iterator iterator = FindMessage(_delayedMessages, prevMessage.GetPackageNumber() + 1);
    return iterator != _delayedMessages.end();
}

MessageData DelayedMessagesProcessor::DeliverMessage(MessageInfo const &prevMessage)
{
    QList<MessageData>::Iterator iterator = FindMessage(_delayedMessages, prevMessage.GetPackageNumber() + 1);
    if (iterator == _delayedMessages.end())
        throw std::logic_error("Message for delivery is not found");
    MessageData data = *iterator;
    _delayedMessages.erase(iterator);
    return data;
}

}

