#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QThread>

#include <exception>
#include <memory>

//#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/ServiceLocator.h"

namespace CalcApp
{

//enum ExecuterState

class ActionExecuter : public QObject
{
    Q_OBJECT
public:
    ActionExecuter(std::shared_ptr<IAction> action, QObject *parent = nullptr);
    void Start();
    void Stop(bool hardStop = true);
    virtual ~ActionExecuter() override;

signals:
    void ActionRunning(QString name);
    void ActionCompleted(QString name);
    void ActionAborted(QString name);
    void ActionFailed(QString name, std::exception_ptr exception);

private:
    std::shared_ptr<IAction> _action;
    std::shared_ptr<QThread> _thread;
};

/*class ActionExecuter : public QThread
{
    Q_OBJECT
public:
    ActionExecuter(Context &context, QList<IAction*> const &chain, QObject *parent = nullptr);

protected:
    virtual void run() override;

private:
    Context &_context;
    QList<IAction*> _chain;

signals:
    void ActionRunning(int index);
    void ActionCompleted(int index);
    void ActionFailed(int index);
    void ActionChainFinished();
};*/

class ActionManager : public QObject
{
    Q_OBJECT
public:
    ActionManager(ServiceLocator const &serviceLocator, QObject *parent = nullptr);

    QStringList Create(QString const &chainName/*, QObject *parent*/);
    void Run();
    void Stop();
    void Clear();

/*private:
    void ExecuterCreate();
    void ExecuterCleanup();

    ServiceLocator _serviceLocator;
    Context _context;
    QList<IAction*> _chain;
    ActionExecuter *_executer;*/

private:
    ServiceLocator _serviceLocator;
    QList<std::shared_ptr<ActionExecuter>> _chain;
    std::shared_ptr<Context> _context;
    int _runningCount;
    bool _hasAborted;

signals:
    void ActionRunning(QString name);
    void ActionCompleted(QString name);
    void ActionAborted(QString name);
    void ActionFailed(QString name, std::exception_ptr exception);
    void ActionChainCompleted();
    void ActionChainAborted();

private slots:
    void ProcessActionRunning(QString name);
    void ProcessActionCompleted(QString name);
    void ProcessActionAborted(QString name);
    void ProcessActionFailed(QString name, std::exception_ptr exception);

/*private slots:
    void ProcessActionFailed(int index);
    void ProcessActionChainFinish();*/
};

}
