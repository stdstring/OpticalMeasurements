#pragma once

#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IAction.h"

namespace CalcApp
{

class TestSaveDataAction : public IAction
{
public:
    TestSaveDataAction(QString const &actionName, QString const &key, QString const &filename, ContextPtr context);

    virtual QString GetName() override;
    //virtual void StartAction(Context &context) override;
    //virtual void Run(Context &context) override;
    virtual void CleanupAtFailure() override;

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;

private:
    void ProcessData();
    void FinishProcessData();
    void ProcessData(bool last);

private:
    QString _actionName;
    QString _key;
    QString _filename;
    // TODO (std_string) : probably move into separate state object
    int _index;
};

}
