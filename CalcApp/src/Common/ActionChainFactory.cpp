#include <QList>
#include <QObject>

#include <algorithm>

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
    std::transform(chainDef.Actions.cbegin(), chainDef.Actions.cend(), dest.begin(), [&storage, &config, parent](ActionDef const &actionDef){
        IActionFactory *factory = storage.FindAction(actionDef.Id);
        return factory->Create(actionDef.Name, actionDef.Args, config, parent);
    });
    return dest;
}

}
