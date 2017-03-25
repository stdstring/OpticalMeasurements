#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QThread>

#include "Common/ComponentStorage.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/MainConfig.h"

namespace CalcApp
{

class ActionExecuter : public QThread
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
    void ActionRunning(int index, QString const &name);
    void ActionFinished(int index, QString const &name);
    void ActionChainFinished();
};

class ActionManager : public QObject
{
    Q_OBJECT
public:
    ActionManager(MainConfig const &config, ComponentStorage const &storage, QObject *parent = nullptr);

    QStringList Create(QString const &chainName, QObject *parent);
    void Run();
    void Stop();
    void Clear();

private:
    void ExecuterCreate();
    void ExecuterCleanup();

    MainConfig const& _config;
    ComponentStorage const& _storage;
    Context _context;
    QList<IAction*> _chain;
    ActionExecuter *_executer;

signals:
    void ActionRunning(int index, QString const &name);
    void ActionFinished(int index, QString const &name);
    void ActionChainFinished();

private slots:
    void ProcessActionChainExecutionFinish();
};

}
