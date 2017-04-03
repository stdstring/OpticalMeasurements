#include <QByteArray>
#include <QDataStream>
#include <QObject>
#include <QString>
#include <QThread>

#include <memory>
#include <stdexcept>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/ITransport.h"
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

}

TransportInteractionHandler::TransportInteractionHandler(ITransportFactory *transportFactory, TransportConfig const &config, QStringListContextItem *contextItem) :
    _transportFactory(transportFactory),
    _transport(nullptr),
    _config(config),
    _contextItem(contextItem),
    _state(ExecutionState::STARTED)
{
}

void TransportInteractionHandler::Start()
{
    _transport = _transportFactory->Create(_config, this);
    QObject::connect(_transport, &ITransport::ResponseReceived, this, &TransportInteractionHandler::ProcessResponse);
    QObject::connect(_transport, &ITransport::DataReceived, this, &TransportInteractionHandler::ProcessData);
    QObject::connect(_transport, &ITransport::EventReceived, this, &TransportInteractionHandler::ProcessEvent);
    _transport->Connect();
    _transport->Send(Message(MessageType::REQUEST, StartCommand.toUtf8()));
}

void TransportInteractionHandler::Stop()
{
    QObject::disconnect(_transport, &ITransport::ResponseReceived, this, &TransportInteractionHandler::ProcessResponse);
    QObject::disconnect(_transport, &ITransport::DataReceived, this, &TransportInteractionHandler::ProcessData);
    QObject::disconnect(_transport, &ITransport::EventReceived, this, &TransportInteractionHandler::ProcessEvent);
    //_transport->Disconnect();
}

void TransportInteractionHandler::ProcessResponse(Message const &message)
{
    QString response(QString::fromUtf8(message.GetData()));
    if (SuccessResponse != response)
        throw std::logic_error("bad response");
    if (ExecutionState::FINISHED == _state)
        emit Finished();
}

void TransportInteractionHandler::ProcessData(Message const &message)
{
    QDataStream stream(message.GetData());
    stream.setVersion(QDataStream::Qt_5_5);
    quint32 packageNumber, calcNumber;
    QByteArray data;
    stream >> packageNumber >> calcNumber >> data;
    _contextItem->Data.append(QString::fromUtf8(data));
}

void TransportInteractionHandler::ProcessEvent(Message const &message)
{
    QString event(QString::fromUtf8(message.GetData()));
    if (FinishEvent == event)
    {
        _state = ExecutionState::FINISHED;
        _transport->Send(Message(MessageType::REQUEST, StopCommand.toUtf8()));
    }
}

TestInteractionAction::TestInteractionAction(QString const &actionName,
                                             QString const &contextKey,
                                             ITransportFactory *transportFactory,
                                             TransportConfig const &config,
                                             QObject *parent) :
    IAction(parent),
    _actionName(actionName),
    _contextKey(contextKey),
    _transportFactory(transportFactory),
    _config(config)
{
}

QString TestInteractionAction::GetName()
{
    return _actionName;
}

void TestInteractionAction::Run(Context &context)
{
    if (!context.HasKey(_contextKey))
        context.Set(_contextKey, std::shared_ptr<IContextItem>(new QStringListContextItem()));
    QStringListContextItem *contextItem = context.GetValue<QStringListContextItem>(_contextKey);
    std::shared_ptr<TransportInteractionHandler> handler(new TransportInteractionHandler(_transportFactory, _config, contextItem));
    std::shared_ptr<QThread> thread(new QThread());
    handler.get()->moveToThread(thread.get());
    thread.get()->moveToThread(thread.get());
    QObject::connect(thread.get(), &QThread::started, handler.get(), &TransportInteractionHandler::Start);
    QObject::connect(thread.get(), &QThread::finished, handler.get(), &TransportInteractionHandler::Stop);
    QObject::connect(handler.get(), &TransportInteractionHandler::Finished, thread.get(), &QThread::quit);
    thread.get()->start();
    thread.get()->wait();
    QObject::disconnect(thread.get(), &QThread::started, handler.get(), &TransportInteractionHandler::Start);
    QObject::disconnect(thread.get(), &QThread::finished, handler.get(), &TransportInteractionHandler::Stop);
    QObject::disconnect(handler.get(), &TransportInteractionHandler::Finished, thread.get(), &QThread::quit);
}

}
