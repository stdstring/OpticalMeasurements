#pragma once

#include <QObject>
#include <QtPlugin>

#include "IComponentInfo.h"
#include "ITransport.h"
#include "TransportConfig.h"

namespace CalcApp
{

class ITransportFactory : public IComponentInfo
{
public:
    virtual ITransport* Create(TransportConfig const &transportConfig, QObject *parent) = 0;
    virtual ComponentType GetComponentType() override { return ComponentType::TRANSPORT; }
};

}

Q_DECLARE_INTERFACE(CalcApp::ITransportFactory, "com.stdstring.CalcApp.ITransportFactory")
