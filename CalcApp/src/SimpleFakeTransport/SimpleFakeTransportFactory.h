#pragma once

#include <QObject>

#include "../CommonLib/ITransportFactory.h"
#include "../CommonLib/TransportConfig.h"

namespace CalcApp
{

class SimpleFakeTransportFactory : public QObject, public ITransportFactory
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::ITransportFactory)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.ITransportFactory" FILE "SimpleFakeTransportFactory.json")
public:
    SimpleFakeTransportFactory() {}

    virtual ITransport* Create(TransportConfig const &config, QObject *parent) override;
};

}
