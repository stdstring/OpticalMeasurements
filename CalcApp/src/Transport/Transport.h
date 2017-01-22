#pragma once

#include <QObject>

#include "DelayedMessagesProcessor.h"
#include "IMessageCheckStrategy.h"
#include "ITransport.h"
#include "MessageInfo.h"
#include "Message.h"

namespace CalcApp
{

class Transport : public ITransport
{
    Q_OBJECT
public:
    explicit Transport(ITransport *transportLowLevel, IMessageCheckStrategy *messageCheckStrategy, QObject *parent);
    virtual void Connect() override;
    virtual void Send(Message const &message) override;

private:
    ITransport *_transportLowLevel;
    DelayedMessagesProcessor _delayedMessagesProcessor;
    MessageInfo _lastProcessedMessage;

private slots:
    void ReceiveData(Message const &message);
};

}

