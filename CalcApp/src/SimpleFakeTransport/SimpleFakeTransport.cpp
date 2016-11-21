#include <QByteArray>
#include <QObject>

#include <exception>
#include <string>

#include "../CommonLib/ITransport.h"
#include "../CommonLib/Message.h"
#include "../CommonLib/MessageType.h"
#include "SimpleFakeTransport.h"

namespace CalcApp
{

const char *CalibrationRequest = "CALIBRATION-REQUEST";
const char *CalibrationResponse = "CALIBRATION-RESPONSE-OK";
const char *RunRequest = "RUN-REQUEST";
const char *RunResponse = "RUN-RESPONSE-OK";
const char *RunStopEvent = "RUN-STOP";
const char *UnknownCommandResponse = "UNKNOWN-COMMAND";

void FillDataMessages(QVector<Message> &dest)
{
    dest.push_back(Message(MessageType::DATA, QByteArray("data portion 1")));
    dest.push_back(Message(MessageType::DATA, QByteArray("data portion 13")));
    dest.push_back(Message(MessageType::DATA, QByteArray("data portion 666")));
    dest.push_back(Message(MessageType::DATA, QByteArray("data portion 13*666")));
}

void FillEventMessages(QVector<Message> &dest)
{
    dest.push_back(Message(MessageType::EVENT, RunStopEvent));
}

SimpleFakeTransport::SimpleFakeTransport(QObject *parent) : QObject(parent)
{
    _state.State = StateId::START;
}

Message SimpleFakeTransport::ProcessControlCmd(Message const &request)
{
    std::string requestData = request.GetData().toStdString();
    if (_state.State == StateId::START && requestData == CalibrationRequest)
    {
        _state.State = StateId::CALIBRATION;
        return Message(MessageType::RESPONSE, QByteArray(CalibrationResponse));
    }
    if (_state.State == StateId::CALIBRATION && requestData == RunRequest)
    {
        _state.State = StateId::RUN;
        FillDataMessages(_state.InputStorage);
        return Message(MessageType::RESPONSE, QByteArray(RunResponse));
    }
    return Message(MessageType::RESPONSE, QByteArray(UnknownCommandResponse));
}

bool SimpleFakeTransport::HasInput() const
{
    return !_state.InputStorage.empty();
}

Message SimpleFakeTransport::RetrieveInput()
{
    if (HasInput())
    {
        Message message = _state.InputStorage.first();
        _state.InputStorage.pop_front();
        if (_state.State == StateId::RUN && _state.InputStorage.empty())
        {
            _state.State = StateId::STOP;
            FillEventMessages(_state.InputStorage);
        }
        if (_state.State == StateId::STOP && _state.InputStorage.empty())
        {
            _state.State = StateId::START;
        }
        return message;
    }
    throw std::logic_error("invalid state");
}

}
