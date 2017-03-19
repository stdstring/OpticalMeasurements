#include <QList>
#include <QObject>
#include <QString>
#include <QThreadPool>

#include <algorithm>
#include <stdexcept>

#include "Common/ActionChainFactory.h"
#include "Common/ActionsConfig.h"
#include "Common/ComponentStorage.h"
#include "Common/IAction.h"
#include "Common/MainConfig.h"
#include "ActionManager.h"

namespace CalcApp
{

namespace
{

ActionChainDef const& FindActionChain(ActionsConfig const &config, QString const &name)
{
    QList<ActionChainDef>::const_iterator iterator = std::find_if(config.Chains.cbegin(),
                                                                  config.Chains.cend(),
                                                                  [&name](ActionChainDef const &chain){ return chain.Name == name; });
    if (iterator == config.Chains.cend())
        throw std::invalid_argument("name");
    return *iterator;
}

}

ActionExecuter::ActionExecuter(Context &context, QList<IAction*> const &chain, QObject *parent) :
    QObject(parent),
    _context(context),
    _chain(chain)
{
}

void ActionExecuter::run()
{
    for (int index = 0; index < _chain.size(); ++index)
    {
        IAction *action = _chain.at(index);
        QString name = action->GetName();
        emit ActionRunning(index, name);
        action->Run(_context);
        emit ActionFinished(index, name);
    }
    emit ActionChainFinished();
}

ActionManager::ActionManager(MainConfig const &config, ComponentStorage const &storage, QObject *parent) :
    QObject(parent),
    _config(config),
    _storage(storage),
    _executer(nullptr)
{
}

void ActionManager::Create(QString const &chainName, QObject *parent)
{
    if (!_chain.isEmpty())
        throw std::logic_error("Action's chain isn't empty");
    ActionChainDef const &chain = FindActionChain(_config.Actions, chainName);
    _chain = ActionChainFactory::Create(chain, _storage, _config, parent);
}

void ActionManager::Run()
{
    if (_executer != nullptr)
        throw std::logic_error("Action's executer is already exist");
    _executer = new ActionExecuter(_context, _chain, this);
    QThreadPool::globalInstance()->start(_executer);
}

void ActionManager::Stop()
{
    if (_executer == nullptr)
        throw std::logic_error("Action's executer is missing");
    QThreadPool::globalInstance()->cancel(_executer);
    delete _executer;
}

void ActionManager::Clear()
{
    std::for_each(_chain.begin(), _chain.end(), [](IAction *action){ delete action; });
    _chain.clear();
}

}
