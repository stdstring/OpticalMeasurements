#include <QObject>

#include <memory>

#include "DelayedMessagesProcessor.h"
#include "DelayedMessagesProcessorHandler.h"

namespace CalcApp
{

DelayedMessagesProcessorHandler::DelayedMessagesProcessorHandler(std::shared_ptr<DelayedMessagesProcessor> processor, QObject *parent) :
    QObject(parent)
{
    QObject::connect(processor.get(), &DelayedMessagesProcessor::MessageProcessFail, this, [this](){ MessageProcessFail = true; });
}

}
