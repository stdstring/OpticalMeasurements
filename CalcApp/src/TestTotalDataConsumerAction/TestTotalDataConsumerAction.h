#pragma once

#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IAction.h"

namespace CalcApp
{

class TestTotalDataConsumerAction : public IAction
{
public:
    TestTotalDataConsumerAction(QString const &name, QString const &key, QString const &filename, ContextPtr context);

    virtual QString GetName() override;
    //virtual void StartAction(Context &context) override;
    //virtual void Run(Context &context) override;
    virtual void CleanupAtFailure() override;

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;

private:
    void ProcessTotalData();

private:
    QString _name;
    QString _key;
    QString _filename;
};

}
