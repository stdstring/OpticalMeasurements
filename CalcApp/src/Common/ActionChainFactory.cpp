#include <QList>
#include <QObject>

#include <algorithm>
#include <iterator>
#include <memory>
#include <stdexcept>

#include "ActionsConfig.h"
#include "IAction.h"
#include "ServiceLocator.h"
#include "ActionChainFactory.h"

namespace CalcApp
{

QList<std::shared_ptr<IAction>> ActionChainFactory::Create(ActionChainDef const &chainDef, ServiceLocator const &serviceLocator, std::shared_ptr<Context> context)
{
    QList<std::shared_ptr<IAction>> dest;
    std::transform(chainDef.Actions.cbegin(), chainDef.Actions.cend(), std::back_inserter(dest), [&serviceLocator, context](ActionDef const &actionDef){
        IActionFactory *factory = serviceLocator.GetStorage()->FindAction(actionDef.Id);
        if (factory == nullptr)
            throw std::invalid_argument(actionDef.Id.toStdString());
        return factory->Create(actionDef.Name, actionDef.Args, serviceLocator, context);
    });
    return dest;
}

}
