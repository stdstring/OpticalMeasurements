#include <QObject>
#include <QThread>

#include <memory>

#include "Common/IAction.h"
#include "ActionExecuter.h"

namespace CalcApp
{

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
    QObject::connect(_action.get(), &IAction::ActionFinished, this, [this](){
        _thread.get()->exit();
        _thread.get()->wait();
        emit ActionCompleted(_actionName);
    });
    QObject::connect(_action.get(), &IAction::ErrorOccured, this, [this](ExceptionData exception){
        _thread.get()->exit();
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
    Q_UNUSED(hardStop)
    if (!_thread.get()->isRunning())
        return;
    //hardStop ? _thread.get()->terminate() : _thread.get()->quit();
    // TODO (std_string) : think about termination
    _thread.get()->quit();
    _thread.get()->wait();
    emit ActionAborted(_actionName);
}

ActionExecuter::~ActionExecuter()
{
    _thread.get()->exit();
    _thread.get()->wait();
}

}

