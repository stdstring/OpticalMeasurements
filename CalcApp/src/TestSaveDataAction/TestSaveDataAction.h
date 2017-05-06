#pragma once

#include <QObject>
#include <QString>

#include<memory>

#include "Common/Context.h"
#include "Common/IAction.h"

namespace CalcApp
{

class TestSaveDataAction : public IAction
{
public:
    explicit TestSaveDataAction(QString const &actionName, QString const &contextKey, QString const &destFilename,  std::shared_ptr<Context> context/*QObject *parent = nullptr*/);

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
