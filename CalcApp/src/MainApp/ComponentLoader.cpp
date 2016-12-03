#include <QObject>
#include <QString>
#include <QPluginLoader>

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
