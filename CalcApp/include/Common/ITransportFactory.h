#pragma once

#include <QObject>
#include <QtPlugin>

#include "Common/TransportConfig.h"
#include "ITransport.h"

namespace CalcApp
{

class ITransportFactory
{
public:
    virtual ITransport* Create(TransportConfig const &transportConfig, QObject *parent) = 0;
};

}

Q_DECLARE_INTERFACE(CalcApp::ITransportFactory, "com.stdstring.CalcApp.ITransportFactory")
