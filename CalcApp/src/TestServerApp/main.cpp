#include <QCommandLineParser>
#include <QCoreApplication>
#include <QList>
#include <QString>

#include <tuple>
#include <memory>

#include "Common/CommonDefs.h"
#include "Common/Logger/ConsoleLogger.h"
#include "Common/Logger/ILogger.h"
#include "Common/Logger/LoggerService.h"
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
    // TODO (std_string) : configurate logger based on config info
    CalcApp::ConsoleLogger logger;
    CalcApp::LoggerService loggerService(CalcApp::LoggerPtr(&logger, [](CalcApp::ILogger*){}));
    CalcApp::TestServerRunner runner(serverConfig, CalcApp::LoggerPtr(&loggerService, [](CalcApp::ILogger*){}));
    runner.Start(messages);
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &runner, &CalcApp::TestServerRunner::Stop);
    return app.exec();
}

