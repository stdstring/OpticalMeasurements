#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>

#include <algorithm>
#include <iterator>
#include <functional>
#include <memory>
#include <stdexcept>

#include "Common/ActionChainFactory.h"
#include "Common/ActionsConfig.h"
#include "Common/Context.h"
#include "Common/ExceptionData.h"
#include "Common/IAction.h"
#include "Common/ServiceLocator.h"
#include "ActionExecuter.h"
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

ActionManager::ActionManager(std::shared_ptr<ServiceLocator> serviceLocator, QObject *parent) :
    QObject(parent),
    _serviceLocator(serviceLocator),
    _context(new Context()),
    _runningCount(0),
    _hasAborted(false)
{
}

QStringList ActionManager::Create(QString const &chainName)
{
    if (!_chain.isEmpty())
            throw std::logic_error("Action's chain isn't empty");
    _runningCount = 0;
    _hasAborted = false;
    ActionChainDef const &chain = FindActionChain(_serviceLocator.get()->GetConfig()->Actions, chainName);
    QList<std::shared_ptr<IAction>> actions = ActionChainFactory::Create(chain, _serviceLocator, _context);
    std::function<std::shared_ptr<ActionExecuter>(std::shared_ptr<IAction>)> executerFactory = [this](std::shared_ptr<IAction> action)
    {
        std::shared_ptr<ActionExecuter> executer(new ActionExecuter(action));
        QObject::connect(executer.get(), &ActionExecuter::ActionRunning, this, &ActionManager::ProcessActionRunning);
        QObject::connect(executer.get(), &ActionExecuter::ActionCompleted, this, &ActionManager::ProcessActionCompleted);
        QObject::connect(executer.get(), &ActionExecuter::ActionAborted, this, &ActionManager::ProcessActionAborted);
        QObject::connect(executer.get(), &ActionExecuter::ActionFailed, this, &ActionManager::ProcessActionFailed);
        return executer;
    };
    std::transform(actions.cbegin(), actions.cend(), std::back_inserter(_chain), executerFactory);
    QStringList dest;
    std::transform(actions.cbegin(), actions.cend(), std::back_inserter(dest), [](std::shared_ptr<IAction> action){ return action.get()->GetName(); });
    return dest;
}

void ActionManager::Run()
{
    if (_runningCount != 0)
        throw std::logic_error("There are running actions in the chain");
    for (std::shared_ptr<ActionExecuter> executer : _chain)
    {
        executer->Start();
    }
}

void ActionManager::Stop()
{
    for (std::shared_ptr<ActionExecuter> executer : _chain)
    {
        executer->Stop(false);
    }
}

void ActionManager::Clear()
{
    if (_runningCount != 0)
        throw std::logic_error("There are running actions in the chain");
    _chain.clear();
}

void ActionManager::ProcessActionRunning(QString name)
{
    _runningCount++;
    emit ActionRunning(name);
}

void ActionManager::ProcessActionCompleted(QString name)
{
    emit ActionCompleted(name);
    _runningCount--;
    if (_runningCount == 0)
        emit (_hasAborted ? ActionChainAborted() : ActionChainCompleted());
}

void ActionManager::ProcessActionAborted(QString name)
{
    emit ActionAborted(name);
    _hasAborted = true;
    _runningCount--;
    if (_runningCount == 0)
        emit ActionChainAborted();
}

void ActionManager::ProcessActionFailed(QString name, ExceptionData exception)
{
    emit ActionFailed(name, exception);
    _hasAborted = true;
    Stop();
    _runningCount--;
    if (_runningCount == 0)
        emit ActionChainAborted();
}

}
