#include <QList>
#include <QCoreApplication>
#include <QString>

#include <tuple>

#include "Common/CommonDefs.h"
#include "Common/Message.h"
#include "TestServerCore/TestServerConfig.h"
#include "TestServerCore/TestServerRunner.h"
#include "ConfigReader.h"

const QString defaultConfigFilename = "TestServer.config";

int main(int argc, char *argv[])
{
    std::tuple<CalcApp::TestServerConfig, QList<CalcApp::MessagePtr>> config = CalcApp::ReadConfig(defaultConfigFilename);
    CalcApp::TestServerConfig &serverConfig = std::get<0>(config);
    QList<CalcApp::MessagePtr> &messages = std::get<1>(config);
    CalcApp::TestServerRunner runner(serverConfig);
    runner.Start(messages);
    QCoreApplication a(argc, argv);
    QObject::connect(&a, &QCoreApplication::aboutToQuit, &runner, &CalcApp::TestServerRunner::Stop);
    return a.exec();
}

