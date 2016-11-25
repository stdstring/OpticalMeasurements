#pragma once

#include <QObject>
#include <QtPlugin>

#include "ICalculator.h"
#include "ITransport.h"

namespace CalcApp
{

class ICalculatorFactory
{
public:
    virtual ICalculator* Create(ITransport *transport, QObject *parent) = 0;
};

}

Q_DECLARE_INTERFACE(CalcApp::ICalculatorFactory, "com.stdstring.CalcApp.ICalculatorFactory")
