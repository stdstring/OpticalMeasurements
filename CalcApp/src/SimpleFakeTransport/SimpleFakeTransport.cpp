#include <QByteArray>
#include <QObject>

#include <exception>
#include <string>

#include "../CommonLib/ControlMessage.h"
#include "../CommonLib/DataMessage.h"
#include "SimpleFakeTransport.h"

namespace CalcApp
{

const char *CalibrationRequest = "CALIBRATION-REQUEST";
const char *CalibrationResponse = "CALIBRATION-RESPONSE-OK";
const char *RunRequest = "RUN-REQUEST";
const char *RunResponse = "RUN-RESPONSE-OK";
const char *RunStopEvent = "RUN-STOP";
const char *UnknownCommandResponse = "UNKNOWN-COMMAND";

void FillDataMessages(QVector<DataMessage> &dest)
{
    dest.push_back(DataMessage(1, QByteArray("data portion 1")));
    dest.push_back(DataMessage(2, QByteArray("data portion 13")));
    dest.push_back(DataMessage(3, QByteArray("data portion 666")));
    dest.push_back(DataMessage(4, QByteArray("data portion 13*666")));
}

void FillEvents(QVector<ControlMessage> &dest)
{
    dest.push_back(ControlMessage(RunStopEvent));
}

SimpleFakeTransport::SimpleFakeTransport(QObject *parent) : QObject(parent)
{
    _state.State = StateId::START;
    _state.DataStorage.clear();
    _state.EventStorage.clear();
}

ControlMessage SimpleFakeTransport::ProcessControlCmd(ControlMessage const &request)
{
    std::string requestData = request.GetData().toStdString();
    if (_state.State == StateId::START && requestData == CalibrationRequest)
    {
        _state.State = StateId::CALIBRATION;
        return ControlMessage(QByteArray(CalibrationResponse));
    }
    if (_state.State == StateId::CALIBRATION && requestData == RunRequest)
    {
        _state.State = StateId::RUN;
        FillDataMessages(_state.DataStorage);
        return ControlMessage(QByteArray(RunResponse));
    }
    return ControlMessage(QByteArray(UnknownCommandResponse));
}

bool SimpleFakeTransport::HasEvents() const
{
    return _state.State == StateId::STOP && !_state.EventStorage.empty();
}

ControlMessage SimpleFakeTransport::RetrieveEvent()
{
    if (HasEvents())
    {
        ControlMessage message = _state.EventStorage.first();
        _state.EventStorage.pop_front();
        if (_state.EventStorage.empty())
            _state.State = StateId::START;
        return message;
    }
    throw std::logic_error("not implemented");
}

bool SimpleFakeTransport::HasData() const
{
    return _state.State == StateId::RUN && !_state.DataStorage.empty();
}

DataMessage SimpleFakeTransport::RetrieveData()
{
    if (HasData())
    {
        DataMessage message = _state.DataStorage.first();
        _state.DataStorage.pop_front();
        if (_state.DataStorage.empty())
        {
            _state.State = StateId::STOP;
            FillEvents(_state.EventStorage);
        }
        return message;
    }
    throw std::logic_error("not implemented");
}

}
