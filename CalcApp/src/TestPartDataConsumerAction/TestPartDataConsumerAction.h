#pragma once

#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IAction.h"

namespace CalcApp
{

class TestPartDataConsumerAction : public IAction
{
public:
    TestPartDataConsumerAction(QString const &name, QString const &key, QString const &filename, ContextPtr context);

    virtual QString GetName() override;
    //virtual void StartAction(Context &context) override;
    //virtual void Run(Context &context) override;

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;

private:
    void ProcessData();
    void FinishProcessData();

private:
    QString _name;
    QString _key;
    QString _filename;
    // TODO (std_string) : probably move into separate state object
    int _index;
};

}
