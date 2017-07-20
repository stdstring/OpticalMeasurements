#pragma once

#include <QList>
#include <QObject>

#include "IMessageCheckStrategy.h"
#include "MessageInfo.h"

#if defined(TRANSPORT_LIBRARY)
#define TRANSPORT_LIBRARY_DLLSPEC Q_DECL_EXPORT
#else
#define TRANSPORT_LIBRARY_DLLSPEC Q_DECL_IMPORT
#endif

namespace CalcApp
{

class TRANSPORT_LIBRARY_DLLSPEC SimpleMessageCheckStrategy : public IMessageCheckStrategy
{
    Q_OBJECT
public:
    SimpleMessageCheckStrategy(quint32 maxDelayedCount, QObject *parent = nullptr);
    virtual bool Check(MessageInfo const &message, QList<MessageData> const &delayedMessages) override;

private:
    int _maxDelayedCount;
};

}
