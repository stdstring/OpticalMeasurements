#include <QApplication>
#include <QList>

#include <memory>

#include "Common/Logger/ILogger.h"
#include "Common/Logger/LoggerService.h"
#include "Common/Logger/QMessageLoggerWrapper.h"
#include "Common/ComponentLoader.h"
#include "Common/ComponentStorage.h"
#include "Common/IComponentInfo.h"
#include "Common/MainConfig.h"
#include "Common/ServiceLocator.h"
#include "DefaultConfigReader.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // TODO (std_string) : probably show splash screen here
    CalcApp::DefaultConfigReader reader;
    CalcApp::MainConfig config = reader.Read(argc, argv);
    // TODO (std_string) : configurate logger based on config info
    CalcApp::QMessageLoggerWrapper logger(CalcApp::LogLevel::DEBUG);
    CalcApp::LoggerService loggerService(std::shared_ptr<CalcApp::ILogger>(&logger, [](CalcApp::ILogger*){}));
    QList<CalcApp::IComponentInfo*> components = CalcApp::ComponentsDirLoader::Load<CalcApp::IComponentInfo>(config.PluginsCommonDir, &app, true);
    CalcApp::ComponentStorage componentStorage;
    componentStorage.AddComponents(components);
    CalcApp::ServiceLocator serviceLocator(std::shared_ptr<CalcApp::MainConfig>(&config, [](CalcApp::MainConfig*){}),
                                           std::shared_ptr<CalcApp::ComponentStorage>(&componentStorage, [](CalcApp::ComponentStorage*){}),
                                           std::shared_ptr<CalcApp::ILogger>(&loggerService, [](CalcApp::ILogger*){}));
    CalcApp::MainWindow w(serviceLocator);
    w.show();
    return app.exec();
}
