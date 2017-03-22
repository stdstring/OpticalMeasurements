#include <QList>
#include <QObject>

#include <algorithm>
#include <iterator>
#include <stdexcept>

#include "ActionChainFactory.h"
#include "ActionsConfig.h"
#include "ComponentStorage.h"
#include "IAction.h"
#include "MainConfig.h"

namespace CalcApp
{

QList<IAction*> ActionChainFactory::Create(ActionChainDef const &chainDef, ComponentStorage const &storage, MainConfig const &config, QObject *parent)
{
    QList<IAction*> dest;
    std::transform(chainDef.Actions.cbegin(), chainDef.Actions.cend(), std::back_inserter(dest), [&storage, &config, parent](ActionDef const &actionDef){
        IActionFactory *factory = storage.FindAction(actionDef.Id);
        if (factory == nullptr)
            throw std::invalid_argument(actionDef.Id.toStdString());
        return factory->Create(actionDef.Name, actionDef.Args, config, parent);
    });
    return dest;
}

}
