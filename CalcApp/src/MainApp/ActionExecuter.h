#pragma once

#include <QObject>
#include <QString>
#include <QThread>

#include <memory>


#include "Common/CommonDefs.h"
#include "Common/ExceptionData.h"

namespace CalcApp
{

class ActionExecuter : public QObject
{
    Q_OBJECT
public:
    ActionExecuter(ActionPtr action, QObject *parent = nullptr);
    void Start();
    void Stop(/*bool hardStop = true*/);
    virtual ~ActionExecuter() override;

signals:
    void ActionRunning(QString name);
    void ActionCompleted(QString name);
    void ActionAborted(QString name);
    void ActionFailed(QString name, ExceptionData exception);

private:
    ActionPtr _action;
    QString _actionName;
    std::shared_ptr<QThread> _thread;
};

}
