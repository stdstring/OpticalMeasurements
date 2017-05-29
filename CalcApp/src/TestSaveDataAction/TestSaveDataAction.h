#pragma once

#include <QObject>
#include <QString>

//#include<memory>

#include "Common/CommonDefs.h"
//#include "Common/Context.h"
#include "Common/IAction.h"

namespace CalcApp
{

class TestSaveDataAction : public IAction
{
public:
    TestSaveDataAction(QString const &actionName, QString const &contextKey, QString const &destFilename, ContextPtr context);

    virtual QString GetName() override;
    /*virtual void StartAction(Context &context) override;*/
    /*virtual void Run(Context &context) override;*/

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;

private:
    QString _actionName;
    QString _contextKey;
    QString _destFilename;
};

}
