#pragma once

#include <QObject>
#include <QVector>
//#include <QtPlugin>

#include "../CommonLib/ITransport.h"
#include "../CommonLib/Message.h"

namespace CalcApp
{

enum StateId { START, CALIBRATION, RUN, STOP };

class SimpleFakeTransportState
{
public:
    StateId State;
    QVector<Message> InputStorage;
};

class SimpleFakeTransport : public QObject, public ITransport
{
    //Q_OBJECT
    //Q_INTERFACES(CalcApp::ITransport)
    //Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.ITransport" FILE "SimpleFakeTransport.json")
public:
    explicit SimpleFakeTransport(QObject *parent = 0);

    // request-response exchange
    virtual Message ProcessControlCmd(Message const &request) override;
    // retrieve data/events
    // TODO (std_string) : think about signals/slots for events
    virtual bool HasInput() const override;
    virtual Message RetrieveInput() override;

private:
    // TODO (std_string) : use State Machine Framework instead of this in future
    SimpleFakeTransportState _state;
};

}
