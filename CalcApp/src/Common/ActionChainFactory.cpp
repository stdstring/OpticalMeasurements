#include <QList>
#include <QObject>

#include <algorithm>
#include <iterator>
#include <stdexcept>

#include "CommonDefs.h"
#include "ActionsConfig.h"
#include "IAction.h"
#include "IActionFactory.h"
#include "ServiceLocator.h"
#include "ActionChainFactory.h"

namespace CalcApp
{

QList<ActionPtr> ActionChainFactory::Create(ActionChainDef const &chainDef, ServiceLocatorPtr serviceLocator, ContextPtr context, ExecutionStatePtr state)
{
    QList<ActionPtr> dest;
    std::transform(chainDef.Actions.cbegin(), chainDef.Actions.cend(), std::back_inserter(dest), [serviceLocator, context, state](ActionDef const &actionDef){
        IActionFactory *factory = serviceLocator.get()->GetStorage()->FindAction(actionDef.Type);
        if (factory == nullptr)
            throw std::invalid_argument(actionDef.Name.toStdString());
        return factory->Create(actionDef.Name, actionDef.Args, serviceLocator, context, state);
    });
    return dest;
}

}
