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

}
