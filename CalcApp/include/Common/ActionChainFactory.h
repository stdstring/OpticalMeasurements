#pragma once

#include <QList>
#include <QObject>

#include <memory>

#include "ActionsConfig.h"
#include "Context.h"
#include "IAction.h"
#include "ServiceLocator.h"

namespace CalcApp
{

class ActionChainFactory
{
public:
    static QList<std::shared_ptr<IAction>> Create(ActionChainDef const &chainDef, std::shared_ptr<ServiceLocator> serviceLocator, std::shared_ptr<Context> context);

    ActionChainFactory() = delete;
    ActionChainFactory(ActionChainFactory const&) = delete;
    ActionChainFactory(ActionChainFactory&&) = delete;
    ActionChainFactory& operator=(ActionChainFactory const&) = delete;
    ActionChainFactory& operator=(ActionChainFactory&&) = delete;
};

}
