#pragma once

#include <QList>
#include <QObject>

#include "MessageInfo.h"

#if defined(TRANSPORT_LIBRARY)
#define TRANSPORT_LIBRARY_DLLSPEC Q_DECL_EXPORT
#else
#define TRANSPORT_LIBRARY_DLLSPEC Q_DECL_IMPORT
#endif

namespace CalcApp
{

class TRANSPORT_LIBRARY_DLLSPEC IMessageCheckStrategy : public QObject
{
public:
    IMessageCheckStrategy(QObject *parent) : QObject(parent) {}
    virtual bool Check(MessageInfo const &message, QList<MessageData> const &delayedMessages) = 0;
};

}
