#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>

#include <memory>

#include "Common/CommonDefs.h"
#include "Common/ExceptionData.h"
#include"ActionExecuter.h"

namespace CalcApp
{

class ActionManager : public QObject
{
    Q_OBJECT
public:
    ActionManager(ServiceLocatorPtr serviceLocator, QObject *parent = nullptr);

    QStringList Create(QString const &chainName);
    void Run();
    void Stop();
    void Clear();

    ActionChainDefPtr GetCurrentChainDef() const;

private:
    void FinishActionChain();

    ServiceLocatorPtr _serviceLocator;
    LoggerPtr _logger;
    ActionChainDefPtr _chainDef;
    QList<std::shared_ptr<ActionExecuter>> _chain;
    ContextPtr _context;
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
    void ProcessActionFailed(QString name, ExceptionData data);
};

}
