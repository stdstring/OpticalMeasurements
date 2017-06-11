#pragma once

#include <QObject>

#include "Common/CommonDefs.h"
#include "Common/ITransport.h"
#include "DelayedMessagesProcessor.h"
#include "IMessageCheckStrategy.h"
#include "MessageInfo.h"


namespace CalcApp
{

class Transport : public ITransport
{
    Q_OBJECT
public:
    explicit Transport(ITransport *transportLowLevel, IMessageCheckStrategy *messageCheckStrategy, QObject *parent = nullptr);
    virtual void Connect() override;
    virtual void Send(MessagePtr message) override;

private:
    ITransport *_transportLowLevel;
    DelayedMessagesProcessor _delayedMessagesProcessor;
    MessageInfo _lastProcessedMessage;

private slots:
    void ReceiveData(MessagePtr message);
    void ProcessDataMessageFail();
};

}

