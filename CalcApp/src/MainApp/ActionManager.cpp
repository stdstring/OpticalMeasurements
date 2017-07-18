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
#include "Common/Logger/ILogger.h"
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
    _logger(serviceLocator.get()->GetLogger()),
    _context(new Context()),
    _runningCount(0),
    _hasAborted(false)
{
}

QStringList ActionManager::Create(QString const &chainName)
{
    if (!_chain.isEmpty())
            throw std::logic_error("Action's chain isn't empty");
    _chainName = chainName;
    _runningCount = 0;
    _hasAborted = false;
    _logger.get()->WriteInfo(QString("Creation of chain with name \"%1\" is started").arg(_chainName));
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
        _logger.get()->WriteInfo(QString("Action with name \"%1\" is created").arg(action.get()->GetName()));
        return executer;
    };
    std::transform(actions.cbegin(), actions.cend(), std::back_inserter(_chain), executerFactory);
    QStringList dest;
    std::transform(actions.cbegin(), actions.cend(), std::back_inserter(dest), [](ActionPtr action){ return action.get()->GetName(); });
    _logger.get()->WriteInfo(QString("Creation of chain with name \"%1\" is completed").arg(_chainName));
    return dest;
}

void ActionManager::Run()
{
    if (_runningCount != 0)
        throw std::logic_error("There are running actions in the chain");
    _logger.get()->WriteInfo(QString("Running of chain with name \"%1\" is started").arg(_chainName));
    for (std::shared_ptr<ActionExecuter> executer : _chain)
    {
        executer->Start();
    }
    _logger.get()->WriteInfo(QString("Running of chain with name \"%1\" is completed").arg(_chainName));
}

void ActionManager::Stop()
{
    _logger.get()->WriteInfo(QString("Stopping of chain with name \"%1\" is started").arg(_chainName));
    for (std::shared_ptr<ActionExecuter> executer : _chain)
    {
        executer->Stop(/*false*/);
    }
    _logger.get()->WriteInfo(QString("Stopping of chain with name \"%1\" is completed").arg(_chainName));
}

void ActionManager::Clear()
{
    if (_runningCount != 0)
        throw std::logic_error("There are running actions in the chain");
    _chain.clear();
    _context.get()->Clear();
    _logger.get()->WriteInfo(QString("Chain with name \"%1\" is cleared").arg(_chainName));
}

void ActionManager::ProcessActionRunning(QString name)
{
    _runningCount++;
    _logger.get()->WriteInfo(QString("Action with name \"%1\" is running").arg(name));
    emit ActionRunning(name);
}

void ActionManager::ProcessActionCompleted(QString name)
{
    _logger.get()->WriteInfo(QString("Action with name \"%1\" is completed").arg(name));
    emit ActionCompleted(name);
    _runningCount--;
    FinishActionChain();
}

void ActionManager::ProcessActionAborted(QString name)
{
    _logger.get()->WriteInfo(QString("Action with name \"%1\" is aborted").arg(name));
    emit ActionAborted(name);
    _hasAborted = true;
    _runningCount--;
    FinishActionChain();
}

void ActionManager::ProcessActionFailed(QString name, ExceptionData data)
{
    // TODO (std_string) : move into separate fun
    try
    {
        std::rethrow_exception (data.Exception);
    }
    catch (std::exception const &exception)
    {
        _logger.get()->WriteError(QString("Action with name \"%1\" is failed due to the following reason: \"%2\"").arg(name).arg(exception.what()));
    }
    catch (...)
    {
        _logger.get()->WriteError(QString("Action with name \"%1\" is failed due to unknown reason").arg(name));
    }
    emit ActionFailed(name, data);
    _hasAborted = true;
    Stop();
    _runningCount--;
    FinishActionChain();
}

void ActionManager::FinishActionChain()
{
    if (_runningCount == 0)
    {
        // TODO (std_string) : think about this
        if (_hasAborted)
        {
            _logger.get()->WriteInfo(QString("Chain with name \"%1\" is aborted").arg(_chainName));
            emit ActionChainAborted();
        }
        else
        {
            _logger.get()->WriteInfo(QString("Chain with name \"%1\" is completed").arg(_chainName));
            emit ActionChainCompleted();
        }
        //emit (_hasAborted ? ActionChainAborted() : ActionChainCompleted());
        _chain.clear();
    }
}

}
