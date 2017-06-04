#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "Common/IComponentInfo.h"
#include "Common/ITransport.h"
#include "Common/ITransportFactory.h"
#include "Common/TransportConfig.h"

namespace CalcApp
{

class TransportFactory : public ITransportFactory
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::ITransportFactory)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.ITransportFactory" FILE "Transport.json")
public:
    explicit TransportFactory(QObject *parent = nullptr);

    // TODO (std_string) : think about using project name
    // TODO (std_string) : think about moving this into global defs
    virtual QString GetType() override { return "Transport"; }
    virtual ITransport* Create(TransportConfig const &transportConfig, QObject *parent) override;
};

}
