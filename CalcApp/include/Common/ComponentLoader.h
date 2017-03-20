#pragma once

#include <QDirIterator>
#include <QList>
#include <QObject>
#include <QString>

namespace CalcApp
{

class ComponentLoader
{
public:
    template<typename TComponent> static TComponent* Load(QString const &location, QObject *parent)
    {
        QObject *obj = Load(location, parent);
        // TODO (std_string) : investigate why this don't work
        //TComponent *component = qobject_cast<TComponent*>(obj);
        TComponent *component = dynamic_cast<TComponent*>(obj);
        if (component == nullptr && obj != nullptr)
            delete obj;
        return component;
    }

    static QObject* Load(QString const &location, QObject *parent);

    ComponentLoader() = delete;
    ComponentLoader(ComponentLoader const&) = delete;
    ComponentLoader(ComponentLoader&&) = delete;
    ComponentLoader& operator=(ComponentLoader const&) = delete;
    ComponentLoader& operator=(ComponentLoader&&) = delete;
};

class ComponentsDirLoader
{
public:
    template<typename TComponent> static QList<TComponent*> Load(QString const &directory, QObject *parent, bool processSubdirectories)
    {
        QDirIterator::IteratorFlag iteratorFlag = processSubdirectories ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;
        // TODO (std_string) : think about name filters
        QDirIterator iterator(directory, {"*.so", "*.dll"}, QDir::Files, iteratorFlag);
        QList<TComponent*> dest;
        while (iterator.hasNext())
        {
            iterator.next();
            TComponent *component = ComponentLoader::Load<TComponent>(iterator.fileInfo().absoluteFilePath(), parent);
            if (component != nullptr)
                dest.append(component);
        }
        return dest;
    }

    static QList<QObject*> Load(QString const &directory, QObject *parent, bool processSubdirectories);

    ComponentsDirLoader() = delete;
    ComponentsDirLoader(ComponentsDirLoader const&) = delete;
    ComponentsDirLoader(ComponentsDirLoader&&) = delete;
    ComponentsDirLoader& operator=(ComponentsDirLoader const&) = delete;
    ComponentsDirLoader& operator=(ComponentsDirLoader&&) = delete;
};

}
