#include <QCoreApplication>
#include <QList>
#include <QObject>
#include <QtGlobal>
#include <QThread>

#include "gtest/gtest.h"

#include "Common/ITransport.h"
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

void SendOutgoingMessage(ITransport *transport, QList<Message> &messages)
{
    if (!messages.isEmpty() && messages.first().GetType() == MessageType::REQUEST)
        transport->Send(messages.takeFirst());
}

}

void ClientHandler::Check(TransportConfig const &config, QList<Message> const &messages)
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

ClientHandler::ClientHandler(TransportConfig const &config, QThread *initThread, QList<Message> const &messages) :
    QObject(nullptr),
    _config(config),
    _transport(nullptr),
    _initThread(initThread),
    _messages(messages)
{
}

void ClientHandler::ProcessStart()
{
    ITransport *transportLowLevel = new TransportLowLevel(_config, this);
    // TODO (std_string) : think about using factory for this
    IMessageCheckStrategy *messageCheckStrategy = new SimpleMessageCheckStrategy(_config.MaxDelayedCount, this);
    _transport = new Transport(transportLowLevel, messageCheckStrategy, this);
    // TODO (std_string) : think about using new syntax
    //QObject::connect(_transport, &ITransport::DataReceived, this, &ClientHandler::ProcessMessage);
    //QObject::connect(_transport, &ITransport::EventReceived, this, &ClientHandler::ProcessMessage);
    //QObject::connect(_transport, &ITransport::ResponseReceived, this, &ClientHandler::ProcessMessage);
    QObject::connect(_transport, SIGNAL(DataReceived(Message const&)), this, SLOT(ProcessMessage(Message const&)));
    QObject::connect(_transport, SIGNAL(EventReceived(Message const&)), this, SLOT(ProcessMessage(Message const&)));
    QObject::connect(_transport, SIGNAL(ResponseReceived(Message const&)), this, SLOT(ProcessMessage(Message const&)));
    _transport->Connect();
    SendOutgoingMessage(_transport, _messages);
}

void ClientHandler::ProcessFinish()
{
    if (_transport != nullptr)
        delete _transport;
    _transport = nullptr;
    this->moveToThread(_initThread);
}

void ClientHandler::ProcessMessage(Message const &message)
{
    EXPECT_FALSE(_messages.isEmpty());
    EXPECT_EQ(_messages.takeFirst(), message);
    if (_messages.isEmpty())
        QThread::currentThread()->exit();
    else
        SendOutgoingMessage(_transport, _messages);
}

}
