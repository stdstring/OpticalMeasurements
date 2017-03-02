#include <QCoreApplication>
#include <QList>
#include <QObject>
#include <QtGlobal>
#include <QThread>

#include "gtest/gtest.h"

#include "Common/ITransport.h"
#include "LowLevel/TransportLowLevel.h"
#include "ClientEntry.h"
#include "ClientHandler.h"
#include "EqualityOperators.h"
#include "IMessageCheckStrategy.h"
#include "SimpleMessageCheckStrategy.h"
#include "TransportConfig.h"
#include "Transport.h"

namespace CalcApp
{

namespace
{

void SendOutgoingMessage(ITransport *transport, ClientEntry const &entry)
{
    if (entry.OutgoingMessage)
        transport->Send(*entry.OutgoingMessage.get());
}

}

void ClientHandler::Check(TransportConfig const &config, QList<ClientEntry> const &entries)
{
    int argc = 0;
    QCoreApplication app(argc, {});
    Q_UNUSED(app);
    ClientHandler handler(config, QThread::currentThread(), entries);
    QThread thread;
    handler.moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, &handler, &ClientHandler::ProcessStart);
    QObject::connect(&thread, &QThread::finished, &handler, &ClientHandler::ProcessFinish);
    thread.start();
    EXPECT_TRUE(thread.wait());
}

ClientHandler::ClientHandler(TransportConfig const &config, QThread *initThread, QList<ClientEntry> const &entries) :
    QObject(nullptr),
    _config(config),
    _transport(nullptr),
    _initThread(initThread),
    _entries(entries)
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
    if (!_entries.isEmpty())
        SendOutgoingMessage(_transport, _entries.first());
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
    EXPECT_FALSE(_entries.isEmpty());
    EXPECT_EQ(_entries.takeFirst().IncomingMessage ,message);
    if (_entries.isEmpty())
        QThread::currentThread()->exit();
    else
        SendOutgoingMessage(_transport, _entries.first());
}

}
