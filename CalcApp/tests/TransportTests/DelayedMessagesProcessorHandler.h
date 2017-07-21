#pragma once

#include <QObject>

#include <memory>

#include "DelayedMessagesProcessor.h"

namespace CalcApp
{

class DelayedMessagesProcessorHandler : QObject
{
    Q_OBJECT
public:
    explicit DelayedMessagesProcessorHandler(std::shared_ptr<DelayedMessagesProcessor> processor, QObject *parent = nullptr);

    bool MessageProcessFail;
};

}
