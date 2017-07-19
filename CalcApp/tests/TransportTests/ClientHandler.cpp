#include <QCoreApplication>
#include <QList>
#include <QObject>
#include <QtGlobal>
#include <QThread>

#include <memory>

#include "gtest/gtest.h"

#include "Common/CommonDefs.h"
#include "Common/ITransport.h"
#include "Common/Message.h"
#include "Common/TransportConfig.h"
#include "LowLevel/TransportLowLevel.h"
#include "ClientHandler.h"
#include "EqualityOperators.h"
#include "IMessageCheckStrategy.h"
#include "SimpleMessageCheckStrategy.h"
#include "Transport.h"

namespace CalcApp
{

namespace
{

void SendOutgoingMessage(ITransport *transport, QList<MessagePtr> &messages)
{
    if (!messages.isEmpty() && messages.first().get()->GetType() == MessageType::REQUEST)
        transport->Send(messages.takeFirst());
}

}

void ClientHandler::Check(TransportConfig const &config, QList<MessagePtr> const &messages)
{
    int argc = 0;
    QCoreApplication app(argc, {});
    Q_UNUSED(app);
    ClientHandler handler(config, QThread::currentThread(), messages);
    QThread thread;
    handler.moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, &handler, &ClientHandler::ProcessStart);
    QObject::connect(&thread, &QThread::finished, &handler, &ClientHandler::ProcessFinish);
    thread.start();
    EXPECT_TRUE(thread.wait());
}

ClientHandler::ClientHandler(TransportConfig const &config, QThread *initThread, QList<MessagePtr> const &messages) :
    QObject(nullptr),
    _config(config),
    _initThread(initThread),
    _messages(messages)
{
}

void ClientHandler::ProcessStart()
{
    // TODO (std_string) : think about using factory for this
    _transport.reset(new Transport(new TransportLowLevel(_config, this),
                                   new SimpleMessageCheckStrategy(_config.MaxDelayedCount, this)));
    QObject::connect(_transport.get(), &ITransport::DataReceived, this, &ClientHandler::ProcessMessage);
    QObject::connect(_transport.get(), &ITransport::EventReceived, this, &ClientHandler::ProcessMessage);
    QObject::connect(_transport.get(), &ITransport::ResponseReceived, this, &ClientHandler::ProcessMessage);
    _transport->Connect();
    SendOutgoingMessage(_transport.get(), _messages);
}

void ClientHandler::ProcessFinish()
{
    _transport.reset();
    this->moveToThread(_initThread);
}

void ClientHandler::ProcessMessage(MessagePtr message)
{
    EXPECT_FALSE(_messages.isEmpty());
    EXPECT_EQ(_messages.takeFirst(), message);
    if (_messages.isEmpty())
        QThread::currentThread()->exit();
    else
        SendOutgoingMessage(_transport.get(), _messages);
}

}
