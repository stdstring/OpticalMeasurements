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
    TestInteractionAction(QString const &name, QString const &key, ITransportFactory *factory, TransportConfig const &config, ContextPtr context);

    virtual QString GetName() override;
    /*virtual void StartAction(Context &context) override;*/
    /*virtual void Run(Context &context) override;*/

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;

private slots:
    void ProcessResponseReceived(MessagePtr message);
    void ProcessDataReceived(MessagePtr message);
    void ProcessDataProcessFailed();
    void ProcessEventReceived(MessagePtr message);

private:
    QString _name;
    QString _key;
    ITransportFactory *_factory;
    TransportConfig const &_config;
    // TODO (std_string) : probably move into separate state object
    enum ExecutionState {STARTED = 0, FINISHED = 1};
    ITransport *_transport;
    ExecutionState _state;
};

}
