#include <QObject>
#include <QQueue>

#include "ActionChainFactory.h"
#include "ActionsConfig.h"
#include "ComponentStorage.h"
#include "IAction.h"
#include "MainConfig.h"

namespace CalcApp
{

QQueue<IAction*> ActionChainFactory::Create(ActionChainDef const &chainDef, ComponentStorage const &storage, MainConfig const &config, QObject *parent)
{
    QQueue<IAction*> chain;
    foreach (ActionDef actionDef, chainDef.Actions)
    {
        IActionFactory *factory = storage.FindAction(actionDef.Id);
        IAction *action = factory->Create(actionDef.Name, actionDef.Args, config, parent);
        chain.enqueue(action);
    }
    return chain;
}

}
