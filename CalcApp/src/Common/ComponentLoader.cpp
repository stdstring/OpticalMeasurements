#include <QDir>
#include <QDirIterator>
#include <QList>
#include <QObject>
#include <QPluginLoader>
#include <QString>

#include "ComponentLoader.h"

namespace CalcApp
{

QObject* ComponentLoader::Load(QString const &location, QObject *parent)
{
    QPluginLoader loader(location);
    QObject *component = loader.instance();
    component->setParent(parent);
    return component;
}

QList<QObject*> ComponentsDirLoader::Load(QString const &directory, QObject *parent, bool processSubdirectories)
{
    QDirIterator::IteratorFlag iteratorFlag = processSubdirectories ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;
    // TODO (std_string) : think about name filters
    QDirIterator iterator(directory, {"*.so", "*.dll"}, QDir::Files, iteratorFlag);
    QList<QObject*> dest;
    while (iterator.hasNext())
    {
        iterator.next();
        QObject *obj = ComponentLoader::Load(iterator.fileInfo().absoluteFilePath(), parent);
        if (obj != nullptr)
            dest.append(obj);
    }
    return dest;
}

}
