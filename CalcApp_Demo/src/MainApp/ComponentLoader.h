#pragma once

#include <QObject>
#include <QString>

namespace CalcApp
{

class ComponentLoader
{
public:
    template<typename TComponent> static TComponent* Load(QString const &location, QObject *parent)
    {
        return qobject_cast<TComponent*>(ComponentLoader::Load(location, parent));
    }

    static QObject* Load(QString const &location, QObject *parent);
};

}
