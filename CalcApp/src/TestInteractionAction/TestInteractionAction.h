#pragma once

#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IAction.h"
#include "Common/ITransport.h"
#include "Common/ITransportFactory.h"
#include "Common/TransportConfig.h"

namespace CalcApp
{

class TestInteractionAction : public IAction
{
public:
    TestInteractionAction(QString const &name, QString const &key, ContextPtr context, ExecutionStatePtr state);

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
    QString _key;
    // TODO (std_string) : probably move into separate state object
    // TODO (std_string) : think about name of enum
    enum InteractionState {STARTED = 0, FINISHED = 1};
    InteractionState _state;
};

}
