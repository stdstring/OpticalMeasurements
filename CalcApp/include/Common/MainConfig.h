#pragma once

#include <QString>

#include "ActionsConfig.h"
#include "TransportConfig.h"

namespace CalcApp
{

class MainConfig
{
public:
    MainConfig(QString const &pluginsCommonDir, ActionsConfig const &actions, TransportConfig const &transport) :
        PluginsCommonDir(pluginsCommonDir),
        Actions(actions),
        Transport(transport)
    {
    }

    QString PluginsCommonDir;
    ActionsConfig Actions;
    TransportConfig Transport;
};

}
