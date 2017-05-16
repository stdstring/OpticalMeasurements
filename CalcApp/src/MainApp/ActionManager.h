#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QThread>

//#include <exception>
#include <memory>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/ServiceLocator.h"

namespace CalcApp
{

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
    void ActionFailed(QString name, ExceptionData exception);

private:
    std::shared_ptr<IAction> _action;
    QString _actionName;
    std::shared_ptr<QThread> _thread;
};

class ActionManager : public QObject
{
    Q_OBJECT
public:
    ActionManager(ServiceLocator const &serviceLocator, QObject *parent = nullptr);

    QStringList Create(QString const &chainName);
    void Run();
    void Stop();
    void Clear();

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
    void ActionFailed(QString name, ExceptionData exception);
    void ActionChainCompleted();
    void ActionChainAborted();

private slots:
    void ProcessActionRunning(QString name);
    void ProcessActionCompleted(QString name);
    void ProcessActionAborted(QString name);
    void ProcessActionFailed(QString name, ExceptionData exception);
};

}
