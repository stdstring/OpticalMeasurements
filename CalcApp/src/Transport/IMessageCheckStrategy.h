#pragma once

#include <QList>
#include <QObject>

#include "MessageInfo.h"

namespace CalcApp
{

class IMessageCheckStrategy : public QObject
{
public:
    IMessageCheckStrategy(QObject *parent) : QObject(parent) {}
    virtual bool Check(MessageInfo const &message, QList<MessageData> const &delayedMessages) = 0;
};

}
