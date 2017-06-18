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
#include "Common/ITransportFactory.h"
#include "Common/Message.h"
#include "Common/TransportConfig.h"
#include "TestInteractionAction.h"

namespace CalcApp
{

namespace
{

const QString StartCommand("START");
const QString StopCommand("STOP");
const QString SuccessResponse("OK");
const QString FinishEvent("EOF");

void ProcessData(QStringListContextItem *item, QByteArray const &data)
{
    QWriteLocker locker(&item->Lock);
    item->Data.append(QString::fromUtf8(data));
}

}

TestInteractionAction::TestInteractionAction(QString const &name, QString const &key, ContextPtr context, ExecutionStatePtr state) :
    IAction(context, state),
    _name(name),
    _key(key),
    _state(InteractionState::STARTED)
{
    context.get()->Set(_key, std::make_shared<QStringListContextItem>());
}

QString TestInteractionAction::GetName()
{
    return _name;
}

/*void TestInteractionAction::StartAction(Context &context)
{
}*/

/*void TestInteractionAction::Run(Context &context)
{
}*/

void TestInteractionAction::ProcessStartImpl()
{
    TransportPtr transport = GetExecutionState().get()->GetTransport();
    QObject::connect(transport.get(), &ITransport::ResponseReceived, this, &TestInteractionAction::ProcessResponseReceived);
    QObject::connect(transport.get(), &ITransport::DataReceived, this, &TestInteractionAction::ProcessDataReceived);
    QObject::connect(transport.get(), &ITransport::DataProcessFailed, this, &TestInteractionAction::ProcessDataProcessFailed);
    QObject::connect(transport.get(), &ITransport::EventReceived, this, &TestInteractionAction::ProcessEventReceived);
    transport.get()->Connect();
    transport.get()->Send(std::make_shared<Message>(MessageType::REQUEST, StartCommand.toUtf8()));
}

void TestInteractionAction::ProcessStopImpl()
{
    TransportPtr transport = GetExecutionState().get()->GetTransport();
    QObject::disconnect(transport.get(), &ITransport::ResponseReceived, this, &TestInteractionAction::ProcessResponseReceived);
    QObject::disconnect(transport.get(), &ITransport::DataReceived, this, &TestInteractionAction::ProcessDataReceived);
    QObject::disconnect(transport.get(), &ITransport::DataProcessFailed, this, &TestInteractionAction::ProcessDataProcessFailed);
    QObject::disconnect(transport.get(), &ITransport::EventReceived, this, &TestInteractionAction::ProcessEventReceived);
}

void TestInteractionAction::CleanupNonFinished()
{
    TransportPtr transport = GetExecutionState().get()->GetTransport();
    transport.get()->Send(std::make_shared<Message>(MessageType::REQUEST, StopCommand.toUtf8()));
}

void TestInteractionAction::ProcessResponseReceived(MessagePtr message)
{
    QString response(QString::fromUtf8(message.get()->GetData()));
    if (SuccessResponse != response)
    {
        ExceptionData exceptionData(std::make_exception_ptr(std::logic_error("bad response")));
        emit ErrorOccured(exceptionData);
        return;
    }
    if (InteractionState::FINISHED == _state)
    {
        emit GetContext().get()->DataCompleted(_key);
        emit ActionFinished();
    }
}

void TestInteractionAction::ProcessDataReceived(MessagePtr message)
{
    QDataStream stream(message.get()->GetData());
    stream.setVersion(DataStreamVersion);
    quint32 packageNumber, calcNumber;
    QByteArray data;
    stream >> packageNumber >> calcNumber >> data;
    QStringListContextItem *item = GetContext().get()->GetValue<QStringListContextItem>(_key);
    ProcessData(item, data);
    item->NotifyDataChange();
}

void TestInteractionAction::ProcessDataProcessFailed()
{
    ExceptionData exceptionData(std::make_exception_ptr(std::logic_error("bad data sequence")));
    emit ErrorOccured(exceptionData);
}

void TestInteractionAction::ProcessEventReceived(MessagePtr message)
{
    QString event(QString::fromUtf8(message.get()->GetData()));
    if (FinishEvent == event)
    {
        TransportPtr transport = GetExecutionState().get()->GetTransport();
        _state = InteractionState::FINISHED;
        transport.get()->Send(std::make_shared<Message>(MessageType::REQUEST, StopCommand.toUtf8()));
    }
}

}
