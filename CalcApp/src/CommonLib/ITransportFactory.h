#pragma once

#include <QObject>
#include <QtPlugin>

#include "ITransport.h"
#include "TransportConfig.h"

namespace CalcApp
{

class ITransportFactory
{
public:
    virtual ITransport* Create(TransportConfig const &config, QObject *parent) = 0;
};

}

Q_DECLARE_INTERFACE(CalcApp::ITransportFactory, "com.stdstring.CalcApp.ITransportFactory")
