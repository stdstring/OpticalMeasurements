#include <QByteArray>
#include <QDataStream>
#include <QObject>
#include <QString>
#include <QWriteLocker>

#include <exception>
#include <memory>
#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/ExceptionData.h"
#include "Common/ExecutionState.h"
#include "Common/IAction.h"
#include "Common/Message.h"
#include "DataReceiverAction.h"

namespace CalcApp
{

namespace
{

typedef QListContextItem<EncodersData> EncodersDataContextItem;

const QString StartCommand("START");
const QString StopCommand("STOP");
const QString SuccessResponse("OK");
const QString FinishEvent("EOF");

void ProcessData(EncodersDataContextItem *item, QByteArray const &data)
{
    Q_UNUSED(data);
    QWriteLocker locker(&item->Lock);
    item->Data.append(EncodersData());
}

}

DataReceiverAction::DataReceiverAction(QString const &name, QString const &key, ContextPtr context, ExecutionStatePtr state) :
    IAction(context, state),
    _name(name),
    _key(key),
    _state(ExchangeState::STARTED)
{
    context.get()->Set(_key, std::make_shared<EncodersDataContextItem>());
}

QString DataReceiverAction::GetName()
{
    return _name;
}

/*void DataReceiverAction::StartAction(Context &context)
{
}*/

/*void DataReceiverAction::Run(Context &context)
{
}*/

void DataReceiverAction::ProcessStartImpl()
{
    TransportPtr transport = GetExecutionState().get()->GetTransport();
    QObject::connect(transport.get(), &ITransport::ResponseReceived, this, &DataReceiverAction::ProcessResponseReceived);
    QObject::connect(transport.get(), &ITransport::DataReceived, this, &DataReceiverAction::ProcessDataReceived);
    QObject::connect(transport.get(), &ITransport::DataProcessFailed, this, &DataReceiverAction::ProcessDataProcessFailed);
    QObject::connect(transport.get(), &ITransport::EventReceived, this, &DataReceiverAction::ProcessEventReceived);
    transport.get()->Connect();
    transport.get()->Send(std::make_shared<Message>(MessageType::REQUEST, StartCommand.toUtf8()));
}

void DataReceiverAction::ProcessStopImpl()
{
    TransportPtr transport = GetExecutionState().get()->GetTransport();
    QObject::disconnect(transport.get(), &ITransport::ResponseReceived, this, &DataReceiverAction::ProcessResponseReceived);
    QObject::disconnect(transport.get(), &ITransport::DataReceived, this, &DataReceiverAction::ProcessDataReceived);
    QObject::disconnect(transport.get(), &ITransport::DataProcessFailed, this, &DataReceiverAction::ProcessDataProcessFailed);
    QObject::disconnect(transport.get(), &ITransport::EventReceived, this, &DataReceiverAction::ProcessEventReceived);
}

void DataReceiverAction::CleanupNonFinished()
{
    TransportPtr transport = GetExecutionState().get()->GetTransport();
    transport.get()->Send(std::make_shared<Message>(MessageType::REQUEST, StopCommand.toUtf8()));
}

void DataReceiverAction::ProcessResponseReceived(MessagePtr message)
{
    QString response(QString::fromUtf8(message.get()->GetData()));
    if (SuccessResponse != response)
    {
        ExceptionData exceptionData(std::make_exception_ptr(std::logic_error("bad response")));
        emit ErrorOccured(exceptionData);
        return;
    }
    if (ExchangeState::FINISHED == _state)
    {
        emit GetContext().get()->DataCompleted(_key);
        emit ActionFinished();
    }
}

void DataReceiverAction::ProcessDataReceived(MessagePtr message)
{
    QDataStream stream(message.get()->GetData());
    stream.setVersion(DataStreamVersion);
    quint32 packageNumber, calcNumber;
    QByteArray data;
    stream >> packageNumber >> calcNumber >> data;
    EncodersDataContextItem *item = GetContext().get()->GetValue<EncodersDataContextItem>(_key);
    ProcessData(item, data);
    item->NotifyDataChange();
}

void DataReceiverAction::ProcessDataProcessFailed()
{
    ExceptionData exceptionData(std::make_exception_ptr(std::logic_error("bad data sequence")));
    emit ErrorOccured(exceptionData);
}

void DataReceiverAction::ProcessEventReceived(MessagePtr message)
{
    QString event(QString::fromUtf8(message.get()->GetData()));
    if (FinishEvent == event)
    {
        TransportPtr transport = GetExecutionState().get()->GetTransport();
        _state = ExchangeState::FINISHED;
        transport.get()->Send(std::make_shared<Message>(MessageType::REQUEST, StopCommand.toUtf8()));
    }
}

}
