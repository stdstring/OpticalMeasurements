#include <QCommandLineParser>
#include <QCoreApplication>
#include <QList>
#include <QString>

#include <tuple>

#include "Common/CommonDefs.h"
#include "Common/Message.h"
#include "TestServerCore/TestServerConfig.h"
#include "TestServerCore/TestServerRunner.h"
#include "CommandLineDefs.h"
#include "ConfigReader.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    CalcApp::CommandLineDefs::CreateDefs(&parser);
    parser.process(app);
    QString configFilename = parser.value(CalcApp::CommandLineDefs::ConfigOptionName);
    std::tuple<CalcApp::TestServerConfig, QList<CalcApp::MessagePtr>> config = CalcApp::ReadConfig(configFilename);
    CalcApp::TestServerConfig &serverConfig = std::get<0>(config);
    QList<CalcApp::MessagePtr> &messages = std::get<1>(config);
    CalcApp::TestServerRunner runner(serverConfig);
    runner.Start(messages);
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &runner, &CalcApp::TestServerRunner::Stop);
    return app.exec();
}

