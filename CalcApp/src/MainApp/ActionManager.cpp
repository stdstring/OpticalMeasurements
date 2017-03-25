#include <QList>
#include <QObject>
#include <QString>
#include <QThread>

#include <algorithm>
#include <iterator>
#include <stdexcept>

#include "Common/ActionChainFactory.h"
#include "Common/ActionsConfig.h"
#include "Common/ComponentStorage.h"
#include "Common/Context.h"
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
    QThread(parent),
    _context(context),
    _chain(chain)
{
}

void ActionExecuter::run()
{
    for (int index = 0; index < _chain.size(); ++index)
    {
        IAction *action = _chain.at(index);
        emit ActionRunning(index);
        action->Run(_context);
        emit ActionFinished(index);
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

QStringList ActionManager::Create(QString const &chainName, QObject *parent)
{
    if (!_chain.isEmpty())
        throw std::logic_error("Action's chain isn't empty");
    ActionChainDef const &chain = FindActionChain(_config.Actions, chainName);
    _chain = ActionChainFactory::Create(chain, _storage, _config, parent);
    QStringList dest;
    std::transform(_chain.cbegin(), _chain.cend(), std::back_inserter(dest), [](IAction *action){ return action->GetName(); });
    return dest;
}

void ActionManager::Run()
{
    if (_executer != nullptr)
        throw std::logic_error("Action's executer is already exist");
    ExecuterCreate();
    _executer->start();
}

void ActionManager::Stop()
{
    if (_executer == nullptr)
        return;
    _executer->terminate();
    ExecuterCleanup();
    emit ActionChainAborted();
}

void ActionManager::Clear()
{
    std::for_each(_chain.begin(), _chain.end(), [](IAction *action){ delete action; });
    _chain.clear();
}

void ActionManager::ExecuterCreate()
{
    _executer = new ActionExecuter(_context, _chain, this);
    QObject::connect(_executer, &ActionExecuter::ActionRunning, this, &ActionManager::ActionRunning);
    QObject::connect(_executer, &ActionExecuter::ActionFinished, this, &ActionManager::ActionFinished);
    QObject::connect(_executer, &ActionExecuter::ActionChainFinished, this, &ActionManager::ProcessActionChainFinish);
}

void ActionManager::ExecuterCleanup()
{
    QObject::disconnect(_executer, &ActionExecuter::ActionRunning, this, &ActionManager::ActionRunning);
    QObject::disconnect(_executer, &ActionExecuter::ActionFinished, this, &ActionManager::ActionFinished);
    QObject::disconnect(_executer, &ActionExecuter::ActionChainFinished, this, &ActionManager::ProcessActionChainFinish);
    _executer->wait();
    delete _executer;
    _executer = nullptr;
}

void ActionManager::ProcessActionChainFinish()
{
    _executer->wait();
    ExecuterCleanup();
    emit ActionChainCompleted();
}

}
