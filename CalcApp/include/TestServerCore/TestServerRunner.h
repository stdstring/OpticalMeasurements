#pragma once

#include <QList>
#include <QObject>
#include <QThread>

#include <memory>

#include "Common/CommonDefs.h"
#include "TestServer.h"
#include "TestServerConfig.h"

namespace CalcApp
{

class TestServerRunner : public QObject
{
    Q_OBJECT
public:
    TestServerRunner(TestServerConfig const &config, LoggerPtr logger, QObject *parent = nullptr);
    void Start(QList<MessagePtr> const &messages);
    void Stop();

private:
    TestServerConfig _config;
    LoggerPtr _logger;
    std::shared_ptr<TestServer> _server;
    QThread *_thread;
};

}
