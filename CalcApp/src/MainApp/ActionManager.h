#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>

#include <memory>

#include "Common/Context.h"
#include "Common/ExceptionData.h"
#include "Common/IAction.h"
#include "Common/ServiceLocator.h"
#include"ActionExecuter.h"

namespace CalcApp
{

class ActionManager : public QObject
{
    Q_OBJECT
public:
    ActionManager(std::shared_ptr<ServiceLocator> serviceLocator, QObject *parent = nullptr);

    QStringList Create(QString const &chainName);
    void Run();
    void Stop();
    void Clear();

private:
    std::shared_ptr<ServiceLocator> _serviceLocator;
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
