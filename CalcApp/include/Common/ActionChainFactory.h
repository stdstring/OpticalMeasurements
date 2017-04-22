#pragma once

#include <QList>
#include <QObject>

#include "ActionsConfig.h"
#include "IAction.h"
#include "ServiceLocator.h"

namespace CalcApp
{

class ActionChainFactory
{
public:
    static QList<IAction*> Create(ActionChainDef const &chainDef, ServiceLocator const &serviceLocator, QObject *parent);

    ActionChainFactory() = delete;
    ActionChainFactory(ActionChainFactory const&) = delete;
    ActionChainFactory(ActionChainFactory&&) = delete;
    ActionChainFactory& operator=(ActionChainFactory const&) = delete;
    ActionChainFactory& operator=(ActionChainFactory&&) = delete;
};

}
