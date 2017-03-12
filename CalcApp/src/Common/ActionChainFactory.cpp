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
}

}
