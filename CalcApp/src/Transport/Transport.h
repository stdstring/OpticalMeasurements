#pragma once

#include <QObject>

#include "Common/CommonDefs.h"
#include "Common/ITransport.h"
#include "DelayedMessagesProcessor.h"
#include "IMessageCheckStrategy.h"
#include "MessageInfo.h"

#if defined(TRANSPORT_LIBRARY)
#define TRANSPORT_LIBRARY_DLLSPEC Q_DECL_EXPORT
#else
#define TRANSPORT_LIBRARY_DLLSPEC Q_DECL_IMPORT
#endif

namespace CalcApp
{

class TRANSPORT_LIBRARY_DLLSPEC Transport : public ITransport
{
    Q_OBJECT
public:
    explicit Transport(ITransport *transportLowLevel, IMessageCheckStrategy *messageCheckStrategy, QObject *parent = nullptr);
    virtual void Connect() override;
    virtual void Send(MessagePtr message) override;
    virtual void Disconnect() override;

private:
    ITransport *_transportLowLevel;
    DelayedMessagesProcessor _delayedMessagesProcessor;
    MessageInfo _lastProcessedMessage;

private slots:
    void ReceiveData(MessagePtr message);
    void ProcessDataMessageFail();
};

}

