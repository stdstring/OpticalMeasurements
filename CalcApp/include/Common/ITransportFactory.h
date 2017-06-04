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
    explicit ITransportFactory(QObject *parent = nullptr) : IComponentInfo(parent) {}

    virtual ITransport* Create(TransportConfig const &transportConfig, QObject *parent) = 0;
    virtual ComponentCategory GetComponentCategory() override { return ComponentCategory::TRANSPORT; }
};

}

Q_DECLARE_INTERFACE(CalcApp::ITransportFactory, "com.stdstring.CalcApp.ITransportFactory")
