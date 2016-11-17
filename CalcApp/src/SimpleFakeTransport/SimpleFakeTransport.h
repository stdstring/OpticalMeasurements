#pragma once

#include <QObject>

#include "../CommonLib/ControlMessage.h"
#include "../CommonLib/DataMessage.h"
#include "../CommonLib/ITransport.h"

namespace CalcApp
{

class SimpleFakeTransport : public QObject, public ITransport
{
public:
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
};

}
