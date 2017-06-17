#pragma once

#include <QObject>
#include <QQueue>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IAction.h"

namespace CalcApp
{

class TestDataGeneratorAction : public IAction
{
public:
    TestDataGeneratorAction(QString const &name, QString const &key, int sleepTime, int dataCount, ContextPtr context);

    virtual QString GetName() override;
    //virtual void StartAction(Context &context) override;
    //virtual void Run(Context &context) override;

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;
    virtual void CleanupNonFinished() override;

private:
    void GenerateNextItem();

private:
    QString _name;
    QString _key;
    int _sleepTime;
    QQueue<int> _data;
};

}
