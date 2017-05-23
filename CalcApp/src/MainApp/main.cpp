#include <QApplication>
#include <QList>
#include <QMetaType>

#include "Common/CommonDefs.h"
#include "Common/Logger/ILogger.h"
#include "Common/Logger/LoggerService.h"
#include "Common/Logger/QMessageLoggerWrapper.h"
#include "Common/ComponentLoader.h"
#include "Common/ComponentStorage.h"
#include "Common/IAction.h"
#include "Common/IComponentInfo.h"
#include "Common/MainConfig.h"
#include "Common/ServiceLocator.h"
#include "DefaultConfigReader.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    // TODO (std_string) : move into separate place
    qRegisterMetaType<CalcApp::ExceptionData>("ExceptionData");
    QApplication app(argc, argv);
    // TODO (std_string) : probably show splash screen here
    CalcApp::DefaultConfigReader reader;
    CalcApp::MainConfig config = reader.Read(argc, argv);
    // TODO (std_string) : configurate logger based on config info
    CalcApp::QMessageLoggerWrapper logger(CalcApp::LogLevel::DEBUG);
    CalcApp::LoggerService loggerService(CalcApp::LoggerPtr(&logger, [](CalcApp::ILogger*){}));
    loggerService.WriteDebug("app is started");
    loggerService.WriteDebug("loading of components is started");
    QList<CalcApp::IComponentInfo*> components = CalcApp::ComponentsDirLoader::Load<CalcApp::IComponentInfo>(config.PluginsCommonDir, &app, true);
    CalcApp::ComponentStorage componentStorage;
    componentStorage.AddComponents(components);
    loggerService.WriteDebug("loading of components is finished");
    CalcApp::ServiceLocator serviceLocator(CalcApp::MainConfigPtr(&config, [](CalcApp::MainConfig*){}),
                                           CalcApp::ComponentStoragePtr(&componentStorage, [](CalcApp::ComponentStorage*){}),
                                           CalcApp::LoggerPtr(&loggerService, [](CalcApp::ILogger*){}));
   CalcApp::MainWindow w(CalcApp::ServiceLocatorPtr(&serviceLocator, [](CalcApp::ServiceLocator*){}));
    w.show();
    int result = app.exec();
    loggerService.WriteDebug("app is finished");
    return result;
}
