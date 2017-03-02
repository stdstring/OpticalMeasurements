#pragma once

/*#include <QList>
#include <QObject>
#include <QThread>

#include <memory>

#include "Common/Message.h"
#include "TestServer.h"
#include "TestServerConfig.h"

namespace CalcApp
{

class TestServerRunner : public QObject
{
    Q_OBJECT
public:
    TestServerRunner(TestServerConfig const &config, QObject *parent = nullptr);
    void Start(QList<Message> const &messages);
    void Stop();

private:
    TestServerConfig _config;
    std::shared_ptr<TestServer> _server;
    QThread *_thread;
};

}*/
