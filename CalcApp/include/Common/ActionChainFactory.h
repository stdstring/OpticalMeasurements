#pragma once

#include <QList>
#include <QObject>

#include "CommonDefs.h"
#include "ActionsConfig.h"

namespace CalcApp
{

class ActionChainFactory
{
public:
    static QList<ActionPtr> Create(ActionChainDef const &chainDef, ServiceLocatorPtr serviceLocator, ContextPtr context);

    ActionChainFactory() = delete;
    ActionChainFactory(ActionChainFactory const&) = delete;
    ActionChainFactory(ActionChainFactory&&) = delete;
    ActionChainFactory& operator=(ActionChainFactory const&) = delete;
    ActionChainFactory& operator=(ActionChainFactory&&) = delete;
};

}
