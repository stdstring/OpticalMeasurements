#include <QObject>
#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/ITransport.h"
#include "Common/Message.h"
#include "MessageInfo.h"
#include "MessageInfoFactory.h"
#include "MessageValidation.h"
#include "Transport.h"

namespace CalcApp
{

Transport::Transport(ITransport *transportLowLevel, IMessageCheckStrategy *messageCheckStrategy, QObject *parent) :
    ITransport(parent),
    _transportLowLevel(transportLowLevel),
    _delayedMessagesProcessor(messageCheckStrategy)
{
    QObject::connect(_transportLowLevel, &ITransport::ResponseReceived, this, &Transport::ResponseReceived);
    QObject::connect(_transportLowLevel, &ITransport::EventReceived, this, &Transport::EventReceived);
    QObject::connect(_transportLowLevel, &ITransport::DataReceived, this, &Transport::ReceiveData);
    QObject::connect(&_delayedMessagesProcessor, &DelayedMessagesProcessor::MessageProcessFail, this, &Transport::ProcessDataMessageFail);
}

void Transport::Connect()
{
    _transportLowLevel->Connect();
}

void Transport::Send(MessagePtr message)
{
    _transportLowLevel->Send(message);
}

void Transport::Disconnect()
{
    _transportLowLevel->Disconnect();
}

void Transport::ReceiveData(MessagePtr message)
{
    MessageInfo messageInfo = CreateMessageInfo(message);
    MessageValidationResult validationResult = IsMessageValid(messageInfo, _lastProcessedMessage);
    // TODO (std_string) : use more functional style
    switch (validationResult)
    {
        case MessageValidationResult::PROCESS:
            emit DataReceived(message);
            _lastProcessedMessage = messageInfo;
            while (_delayedMessagesProcessor.CanDeliverMessage(_lastProcessedMessage))
            {
                MessageData data = _delayedMessagesProcessor.DeliverMessage(_lastProcessedMessage);
                emit DataReceived(data.second);
                _lastProcessedMessage = data.first;
            }
            break;
        case MessageValidationResult::DELAY:
            _delayedMessagesProcessor.AddDelayedMessage(messageInfo, message);
            break;
        case MessageValidationResult::SKIP:
            break;
        default:
            throw std::logic_error("Unknown validation result of message");
    }
}

void Transport::ProcessDataMessageFail()
{
    QObject::disconnect(_transportLowLevel, &ITransport::DataReceived, this, &Transport::ReceiveData);
    emit DataProcessFailed();
}

}
