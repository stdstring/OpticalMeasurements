#pragma once

#include <QList>
#include <QString>

#include "ActionsConfig.h"
#include "TransportConfig.h"

namespace CalcApp
{

// TODO (std_string) : move into another place
class CommonConfig
{
public:
    CommonConfig(QString const &pluginsCommonDir) : PluginsCommonDir(pluginsCommonDir)
    {
    }

    QString PluginsCommonDir;
};

// TODO (std_string) : move into another place
class ViewerDef
{
public:
    ViewerDef(QString const &name, QString const &filename, QString const &args) :
        Name(name),
        Filename(filename),
        Args(args)
    {
    }

    QString Name;
    QString Filename;
    QString Args;
};

// TODO (std_string) : move into another place
class ViewersConfig
{
public:
    ViewersConfig(QList<ViewerDef> const &viewers) : Viewers(viewers)
    {
    }

    QList<ViewerDef> Viewers;
};

class MainConfig
{
public:
    /*MainConfig(QString const &pluginsCommonDir, ActionsConfig const &actions, TransportConfig const &transport) :
        PluginsCommonDir(pluginsCommonDir),
        Actions(actions),
        Transport(transport)
    {
    }*/
    MainConfig(CommonConfig const &commonConfig,
               TransportConfig const &transport,
               ViewersConfig const &viewers,
               ActionsConfig const &actions) :
        Common(commonConfig),
        Transport(transport),
        Viewers(viewers),
        Actions(actions)
    {
    }

    CommonConfig Common;
    TransportConfig Transport;
    ViewersConfig Viewers;
    ActionsConfig Actions;
};

}
