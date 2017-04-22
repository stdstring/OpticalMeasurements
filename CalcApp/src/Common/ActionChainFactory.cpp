#include <QList>
#include <QObject>

#include <algorithm>
#include <iterator>
#include <stdexcept>

#include "ActionsConfig.h"
#include "IAction.h"
#include "ServiceLocator.h"
#include "ActionChainFactory.h"

namespace CalcApp
{

QList<IAction*> ActionChainFactory::Create(ActionChainDef const &chainDef, ServiceLocator const &serviceLocator, QObject *parent)
{
    QList<IAction*> dest;
    std::transform(chainDef.Actions.cbegin(), chainDef.Actions.cend(), std::back_inserter(dest), [&serviceLocator, parent](ActionDef const &actionDef){
        IActionFactory *factory = serviceLocator.GetStorage()->FindAction(actionDef.Id);
        if (factory == nullptr)
            throw std::invalid_argument(actionDef.Id.toStdString());
        return factory->Create(actionDef.Name, actionDef.Args, serviceLocator, parent);
    });
    return dest;
}

}
