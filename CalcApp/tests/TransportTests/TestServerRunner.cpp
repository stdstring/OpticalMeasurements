/*#include <QList>
#include <QObject>
#include <QThread>

#include "Common/Message.h"
#include "TestServer.h"
#include "TestServerConfig.h"
#include "TestServerRunner.h"

namespace CalcApp
{

TestServerRunner::TestServerRunner(TestServerConfig const &config, QObject *parent) :
    QObject(parent),
    _config(config),
    _thread(new QThread(this))
{
}

void TestServerRunner::Start(const QList<Message> &messages)
{
    _server.reset(new TestServer(_config, messages, nullptr));
    _server.get()->moveToThread(_thread);
    QObject::connect(_thread, &QThread::started, _server.get(), &TestServer::Start);
    QObject::connect(_thread, &QThread::finished, _server.get(), &TestServer::Stop);
    _thread->start();
}

void TestServerRunner::Stop()
{
    _thread->exit();
    _thread->wait();
    QObject::disconnect(_thread, &QThread::started, _server.get(), &TestServer::Start);
    QObject::disconnect(_thread, &QThread::finished, _server.get(), &TestServer::Stop);
    _server.reset();
}

}*/
