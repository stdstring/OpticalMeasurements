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

TestInteractionAction::TestInteractionAction(QString const &name, QString const &key, ITransportFactory *factory, TransportConfig const &config, ContextPtr context) :
    IAction(context),
    _name(name),
    _key(key),
    _factory(factory),
    _config(config),
    _transport(nullptr),
    _state(ExecutionState::STARTED)
{
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
    // TODO (std_string) : think about place of creation and hold of transport
    _transport = _factory->Create(_config, this);
    QObject::connect(_transport, &ITransport::ResponseReceived, this, &TestInteractionAction::ProcessResponseReceived);
    QObject::connect(_transport, &ITransport::DataReceived, this, &TestInteractionAction::ProcessDataReceived);
    QObject::connect(_transport, &ITransport::DataProcessFailed, this, &TestInteractionAction::ProcessDataProcessFailed);
    QObject::connect(_transport, &ITransport::EventReceived, this, &TestInteractionAction::ProcessEventReceived);
    _transport->Connect();
}

void TestInteractionAction::ProcessStopImpl()
{
    //_transport->Disconnect();
    QObject::disconnect(_transport, &ITransport::ResponseReceived, this, &TestInteractionAction::ProcessResponseReceived);
    QObject::disconnect(_transport, &ITransport::DataReceived, this, &TestInteractionAction::ProcessDataReceived);
    QObject::disconnect(_transport, &ITransport::DataProcessFailed, this, &TestInteractionAction::ProcessDataProcessFailed);
    QObject::disconnect(_transport, &ITransport::EventReceived, this, &TestInteractionAction::ProcessEventReceived);
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
    if (ExecutionState::FINISHED == _state)
        emit ActionFinished();
}

void TestInteractionAction::ProcessDataReceived(MessagePtr message)
{
    QDataStream stream(message.get()->GetData());
    stream.setVersion(QDataStream::Qt_5_5);
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
        _state = ExecutionState::FINISHED;
        _transport->Send(std::make_shared<Message>(MessageType::REQUEST, StopCommand.toUtf8()));
    }
}

}
