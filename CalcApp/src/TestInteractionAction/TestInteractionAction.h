#pragma once

#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IAction.h"
//#include "Common/ITransport.h"
#include "Common/ITransportFactory.h"
//#include "Common/Message.h"
#include "Common/TransportConfig.h"

namespace CalcApp
{

/*class TransportInteractionHandler : public QObject
{
    Q_OBJECT
public:
    TransportInteractionHandler(ITransportFactory *transportFactory, TransportConfig const &config, QStringListContextItem *contextItem);

private:
    enum ExecutionState {STARTED, FINISHED};

    ITransportFactory *_transportFactory;
    ITransport *_transport;
    TransportConfig const &_config;
    QStringListContextItem *_contextItem;
    ExecutionState _state;

signals:
    void Finished();

public slots:
    void Start();
    void Stop();

private slots:
    void ProcessResponse(Message const &message);
    void ProcessData(Message const &message);
    void ProcessEvent(Message const &message);
};*/

class TestInteractionAction : public IAction
{
public:
    TestInteractionAction(QString const &actionName,
                          QString const &contextKey,
                          ITransportFactory *transportFactory,
                          TransportConfig const &config,
                          ContextPtr context);

    virtual QString GetName() override;
    /*virtual void StartAction(Context &context) override;*/
    /*virtual void Run(Context &context) override;*/

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;

private:
    QString _actionName;
    QString _contextKey;
    ITransportFactory *_transportFactory;
    TransportConfig const &_config;
};

}
