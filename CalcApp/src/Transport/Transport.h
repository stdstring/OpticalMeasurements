#pragma once

#include <QObject>

#include "DelayedMessagesProcessor.h"
#include "ITransport.h"
#include "MessageInfo.h"
#include "Message.h"

namespace CalcApp
{

class Transport : public ITransport
{
    Q_OBJECT
public:
    explicit Transport(ITransport *transportLowLevel, QObject *parent);
    virtual void Connect() override;
    virtual void Send(Message const &message) override;

private:
    ITransport *_transportLowLevel;
    DelayedMessagesProcessor _delayedMessagesProcessor;
    MessageInfo _currentMessage;
};

}

