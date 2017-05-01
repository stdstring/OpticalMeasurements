#pragma once

//#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>
//#include <QThread>

//#include "Common/Context.h"
//#include "Common/IAction.h"
#include "Common/ServiceLocator.h"

namespace CalcApp
{

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

    QStringList Create(QString const &chainName, QObject *parent);
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

signals:
    void ActionRunning(int index);
    void ActionCompleted(int index);
    void ActionFailed(int index);
    void ActionChainCompleted();
    void ActionChainAborted();

/*private slots:
    void ProcessActionFailed(int index);
    void ProcessActionChainFinish();*/
};

}
