#include <QApplication>
#include <QList>

#include "Common/ComponentLoader.h"
#include "Common/ComponentStorage.h"
#include "Common/IComponentInfo.h"
#include "Common/MainConfig.h"
#include "DefaultConfigReader.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // TODO (std_string) : probably show splash screen here
    CalcApp::DefaultConfigReader reader;
    CalcApp::MainConfig config = reader.Read(argc, argv);
    QList<CalcApp::IComponentInfo*> components = CalcApp::ComponentsDirLoader::Load<CalcApp::IComponentInfo>(config.PluginsCommonDir, &app, true);
    CalcApp::ComponentStorage componentStorage;
    componentStorage.AddComponents(components);
    CalcApp::MainWindow w(config, componentStorage);
    w.show();
    return app.exec();
}
