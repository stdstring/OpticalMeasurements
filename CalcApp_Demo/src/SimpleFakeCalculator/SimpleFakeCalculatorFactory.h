#pragma once

#include <QObject>
#include <QtPlugin>

#include "../CommonLib/ICalculator.h"
#include "../CommonLib/ICalculatorFactory.h"
#include "../CommonLib/ITransport.h"

namespace CalcApp
{

class SimpleFakeCalculatorFactory : public QObject, public ICalculatorFactory
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::ICalculatorFactory)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.ICalculatorFactory" FILE "SimpleFakeCalculatorFactory.json")
public:
    SimpleFakeCalculatorFactory() {}

    virtual ICalculator* Create(ITransport *transport, QObject *parent) override;
};

}
