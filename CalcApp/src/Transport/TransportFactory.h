#pragma once

#include <QObject>
#include <QString>

#include "Common/IComponentInfo.h"
#include "Common/ITransport.h"
#include "Common/ITransportFactory.h"
#include "Common/TransportConfig.h"

namespace CalcApp
{

class TransportFactory : public QObject, public ITransportFactory
{
    Q_OBJECT
public:
    explicit TransportFactory(QObject *parent = 0);

    // TODO (std_string) : think about using project name
    // TODO (std_string) : think about moving this into global defs
    virtual QString GetId() override { return "Transport"; }
    virtual ITransport* Create(TransportConfig const &transportConfig, QObject *parent) override;
};

}
