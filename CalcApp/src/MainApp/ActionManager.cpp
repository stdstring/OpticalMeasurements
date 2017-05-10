//#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QThread>

//#include <algorithm>
//#include <iterator>
#include <stdexcept>

//#include "Common/ActionChainFactory.h"
//#include "Common/ActionsConfig.h"
//#include "Common/Context.h"
//#include "Common/IAction.h"
#include "Common/ServiceLocator.h"
#include "ActionManager.h"

namespace CalcApp
{

/*namespace
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
        try
        {
            action->Run(_context);
            emit ActionCompleted(index);
        }
        catch (...)
        {
            // TODO (std_string) : think about logging
            emit ActionFailed(index);
            return;
        }
    }
    emit ActionChainFinished();
}*/

ActionExecuter::ActionExecuter(std::shared_ptr<IAction> action, int index, QObject *parent) :
    QObject(parent),
    _action(action),
    _thread(new QThread()),
    _index(index)
{
    _action.get()->moveToThread(_thread.get());
    //_thread.get()->moveToThread(_thread.get());
    //QObject::connect(_thread.get(), &QThread::started, _action.get(), &IAction::ProcessStart);
    //QObject::connect(_thread.get(), &QThread::finished, _action.get(), &IAction::ProcessStop);
    //QObject::connect(_action.get(), &IAction::ActionFinished, _thread.get(), &QThread::quit);
    QObject::connect(_action.get(), &IAction::ErrorOccured, this, [this](std::exception_ptr exception){ emit ActionFailed(_action.get()->GetName(), exception); });
}

void ActionExecuter::Start()
{
    _thread->start();
}

void ActionExecuter::Stop(bool hardStop)
{
    hardStop ? _thread->terminate() : _thread->quit();
    _thread->wait();
}

ActionExecuter::~ActionExecuter()
{
    _thread.get()->quit();
    _thread.get()->wait();
}

ActionManager::ActionManager(ServiceLocator const &serviceLocator, QObject *parent) :
    QObject(parent),
    _serviceLocator(serviceLocator)
    /*_executer(nullptr)*/
{
}

QStringList ActionManager::Create(QString const &chainName/*, QObject *parent*/)
{
    /*if (!_chain.isEmpty())
        throw std::logic_error("Action's chain isn't empty");
    ActionChainDef const &chain = FindActionChain(_serviceLocator.GetConfig().get()->Actions, chainName);
    _chain = ActionChainFactory::Create(chain, _serviceLocator, parent);
    QStringList dest;
    std::transform(_chain.cbegin(), _chain.cend(), std::back_inserter(dest), [](IAction *action){ return action->GetName(); });
    return dest;*/
    return QStringList();
}

void ActionManager::Run()
{
    /*if (_executer != nullptr)
        throw std::logic_error("Action's executer is already exist");
    ExecuterCreate();
    _executer->start();*/
    for (std::shared_ptr<ActionExecuter> executer : _chain)
    {
    }
}

void ActionManager::Stop()
{
    /*if (_executer == nullptr)
        return;
    _executer->terminate();
    ExecuterCleanup();
    emit ActionChainAborted();*/
    for (std::shared_ptr<ActionExecuter> executer : _chain)
    {
    }
}

void ActionManager::Clear()
{
    /*std::for_each(_chain.begin(), _chain.end(), [](IAction *action){ delete action; });
    _chain.clear();*/
    _chain.clear();
}

/*void ActionManager::ExecuterCreate()
{
    _executer = new ActionExecuter(_context, _chain, this);
    QObject::connect(_executer, &ActionExecuter::ActionRunning, this, &ActionManager::ActionRunning);
    QObject::connect(_executer, &ActionExecuter::ActionCompleted, this, &ActionManager::ActionCompleted);
    QObject::connect(_executer, &ActionExecuter::ActionFailed, this, &ActionManager::ProcessActionFailed);
    QObject::connect(_executer, &ActionExecuter::ActionChainFinished, this, &ActionManager::ProcessActionChainFinish);
}

void ActionManager::ExecuterCleanup()
{
    _executer->wait();
    QObject::disconnect(_executer, &ActionExecuter::ActionRunning, this, &ActionManager::ActionRunning);
    QObject::disconnect(_executer, &ActionExecuter::ActionCompleted, this, &ActionManager::ActionCompleted);
    QObject::disconnect(_executer, &ActionExecuter::ActionFailed, this, &ActionManager::ProcessActionFailed);
    QObject::disconnect(_executer, &ActionExecuter::ActionChainFinished, this, &ActionManager::ProcessActionChainFinish);
    delete _executer;
    _executer = nullptr;
}

void ActionManager::ProcessActionFailed(int index)
{
    emit ActionFailed(index);
    ExecuterCleanup();
    emit ActionChainAborted();
}

void ActionManager::ProcessActionChainFinish()
{
    ExecuterCleanup();
    emit ActionChainCompleted();
}*/

}
