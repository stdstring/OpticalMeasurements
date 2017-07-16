#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <QObject>
#include <QPluginLoader>
#include <QStringList>
#include <QTextStream>

#include "IService.h"
#include "IServiceFactory.h"

QStringList GetFiles(QDirIterator &iterator)
{
    QStringList list;
    while (iterator.hasNext())
    {
        list.append(iterator.next());
    }
    return list;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QDirIterator iterator("../PlugingLib", {"PlugingLib.dll"}, QDir::Files, QDirIterator::Subdirectories);
    QStringList files = GetFiles(iterator);
    QString pluginLocation = files.at(0);
    QPluginLoader loader(pluginLocation);
    QObject *component = loader.instance();
    component->setParent(&app);
    PlugingUsing::IServiceFactory *factory = dynamic_cast<PlugingUsing::IServiceFactory*>(component);
    PlugingUsing::IService *service = factory->Create();
    service->DoIt();
    return app.exec();
}
