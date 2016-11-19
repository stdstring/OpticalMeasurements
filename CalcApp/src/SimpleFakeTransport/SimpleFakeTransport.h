#pragma once

#include <QObject>
#include <QVector>
#include <QtPlugin>

#include "../CommonLib/ControlMessage.h"
#include "../CommonLib/DataMessage.h"
#include "../CommonLib/ITransport.h"

namespace CalcApp
{

enum StateId { START, CALIBRATION, RUN, STOP };

class SimpleFakeTransportState
{
public:
    StateId State;
    QVector<DataMessage> DataStorage;
    QVector<ControlMessage> EventStorage;
};

class SimpleFakeTransport : public QObject, public ITransport
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::ITransport)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.ITransport" FILE "SimpleFakeTransport.json")
public:
    explicit SimpleFakeTransport(QObject *parent = 0);

    // exchange
    virtual ControlMessage ProcessControlCmd(ControlMessage const &request) override;
    // events
    // TODO (std_string) : think about signals/slots for events
    virtual bool HasEvents() const override;
    virtual ControlMessage RetrieveEvent() override;
    // data
    // TODO (std_string) : think about signals/slots for data
    virtual bool HasData() const override;
    virtual DataMessage RetrieveData() override;

private:
    // TODO (std_string) : use State Machine Framework instead of this in future
    SimpleFakeTransportState _state;
};

}
