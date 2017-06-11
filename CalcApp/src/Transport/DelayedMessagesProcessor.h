#pragma once

#include <QList>
#include <QObject>

#include "Common/CommonDefs.h"
#include "IMessageCheckStrategy.h"
#include "MessageInfo.h"

namespace CalcApp
{

class DelayedMessagesProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DelayedMessagesProcessor(IMessageCheckStrategy *messageCheckStrategy, QObject *parent = nullptr);
    void AddDelayedMessage(MessageInfo const &info, MessagePtr message);
    bool CanDeliverMessage(MessageInfo const &prevMessage);
    MessageData DeliverMessage(MessageInfo const &prevMessage);

private:
    QList<MessageData> _delayedMessages;
    IMessageCheckStrategy *_messageCheckStrategy;

signals:
    void MessageProcessFail();
};

}
