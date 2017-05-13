#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QThread>

#include <algorithm>
#include <iterator>
#include <memory>
#include <stdexcept>

#include "Common/ActionChainFactory.h"
#include "Common/ActionsConfig.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/ServiceLocator.h"
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

ActionExecuter::ActionExecuter(std::shared_ptr<IAction> action, QObject *parent) :
    QObject(parent),
    _action(action),
    _actionName(action.get()->GetName()),
    _thread(new QThread())
{
    _action.get()->moveToThread(_thread.get());
    //_thread.get()->moveToThread(_thread.get());
    QObject::connect(_thread.get(), &QThread::started, _action.get(), &IAction::ProcessStart);
    QObject::connect(_thread.get(), &QThread::started, this, [this](){ emit ActionRunning(_actionName); });
    QObject::connect(_thread.get(), &QThread::finished, _action.get(), &IAction::ProcessStop);
    //QObject::connect(_action.get(), &IAction::ActionFinished, _thread.get(), &QThread::quit);
    QObject::connect(_action.get(), &IAction::ActionFinished, this, [this](){
        _thread.get()->quit();
        _thread.get()->wait();
        emit ActionCompleted(_actionName);
    });
    //QObject::connect(_action.get(), &IAction::ErrorOccured, this, [this](std::exception_ptr exception){ emit ActionFailed(_action.get()->GetName(), exception); });
    QObject::connect(_action.get(), &IAction::ErrorOccured, this, [this](std::exception_ptr exception){
        _thread.get()->quit();
        _thread.get()->wait();
        emit ActionFailed(_action.get()->GetName(), exception);
    });
}

void ActionExecuter::Start()
{
    _thread->start();
}

void ActionExecuter::Stop(bool hardStop)
{
    if (!_thread.get()->isRunning())
        return;
    hardStop ? _thread.get()->terminate() : _thread.get()->quit();
    _thread.get()->wait();
    emit ActionAborted(_actionName);
}

ActionExecuter::~ActionExecuter()
{
    _thread.get()->quit();
    _thread.get()->wait();
}

ActionManager::ActionManager(ServiceLocator const &serviceLocator, QObject *parent) :
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
    ActionChainDef const &chain = FindActionChain(_serviceLocator.GetConfig().get()->Actions, chainName);
    QList<std::shared_ptr<IAction>> actions = ActionChainFactory::Create(chain, _serviceLocator, _context);
    std::transform(actions.cbegin(),
                   actions.cend(),
                   std::back_inserter(_chain),
                   [](std::shared_ptr<IAction> action){ return std::shared_ptr<ActionExecuter>(new ActionExecuter(action)); });
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
        executer->Stop();
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

void ActionManager::ProcessActionFailed(QString name, std::exception_ptr exception)
{
    emit ActionFailed(name, exception);
    _runningCount--;
    if (_runningCount == 0)
        emit ActionChainAborted();
}

}
