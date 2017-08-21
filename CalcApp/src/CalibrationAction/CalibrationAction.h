#pragma once

#include <QByteArray>
#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IAction.h"

namespace CalcApp
{

class CalibrationAction : public IAction
{
public:
    CalibrationAction(QString const &name, QByteArray const &sourceData, QString const &key, ContextPtr context, ExecutionStatePtr state);

    virtual QString GetName() override;
    /*virtual void StartAction(Context &context) override;*/
    /*virtual void Run(Context &context) override;*/

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;
    virtual void CleanupNonFinished() override;

private slots:
    void ProcessResponseReceived(MessagePtr message);
    void ProcessDataReceived(MessagePtr message);
    void ProcessDataProcessFailed();
    void ProcessEventReceived(MessagePtr message);

private:
    QString _name;
    QByteArray _sourceData;
    QString _key;
};

}
