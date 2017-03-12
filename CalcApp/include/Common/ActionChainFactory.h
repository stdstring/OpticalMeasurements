#pragma once

#include <QObject>
#include <QQueue>

#include "ActionsConfig.h"
#include "ComponentStorage.h"
#include "IAction.h"
#include "MainConfig.h"

namespace CalcApp
{

class ActionChainFactory
{
public:
    static QQueue<IAction*> Create(ActionChainDef const &chainDef, ComponentStorage const &storage, MainConfig const &config, QObject *parent);

    ActionChainFactory() = delete;
    ActionChainFactory(ActionChainFactory const&) = delete;
    ActionChainFactory(ActionChainFactory&&) = delete;
    ActionChainFactory& operator=(ActionChainFactory const&) = delete;
    ActionChainFactory& operator=(ActionChainFactory&&) = delete;
};

}
