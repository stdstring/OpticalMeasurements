#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>

#include <algorithm>
#include <iterator>
#include <functional>
#include <memory>
#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/ActionChainFactory.h"
#include "Common/ActionsConfig.h"
#include "Common/Context.h"
#include "Common/ExecutionState.h"
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

ActionManager::ActionManager(ServiceLocatorPtr serviceLocator, QObject *parent) :
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
    MainConfigPtr config = _serviceLocator.get()->GetConfig();
    ITransportFactory *transportFactory = _serviceLocator.get()->GetStorage()->GetTransport();
    ActionChainDef const &chain = FindActionChain(config->Actions, chainName);
    ExecutionStatePtr executionState(std::make_shared<ExecutionState>(transportFactory, config.get()->Transport));
    QList<ActionPtr> actions = ActionChainFactory::Create(chain, _serviceLocator, _context, executionState);
    std::function<std::shared_ptr<ActionExecuter>(ActionPtr)> executerFactory = [this](ActionPtr action)
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
    std::transform(actions.cbegin(), actions.cend(), std::back_inserter(dest), [](ActionPtr action){ return action.get()->GetName(); });
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
        executer->Stop(/*false*/);
    }
}

void ActionManager::Clear()
{
    if (_runningCount != 0)
        throw std::logic_error("There are running actions in the chain");
    _chain.clear();
    _context.get()->Clear();
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
    FinishActionChain();
}

void ActionManager::ProcessActionAborted(QString name)
{
    emit ActionAborted(name);
    _hasAborted = true;
    _runningCount--;
    FinishActionChain();
}

void ActionManager::ProcessActionFailed(QString name, ExceptionData exception)
{
    emit ActionFailed(name, exception);
    _hasAborted = true;
    Stop();
    _runningCount--;
    FinishActionChain();
}

void ActionManager::FinishActionChain()
{
    if (_runningCount == 0)
    {
        emit (_hasAborted ? ActionChainAborted() : ActionChainCompleted());
        _chain.clear();
    }
}

}
