#pragma once

#include <QObject>

#include "../CommonLib/ICalculator.h"
#include "../CommonLib/ICalculatorFactory.h"
#include "../CommonLib/ITransport.h"

namespace CalcApp
{

class SimpleFakeCalculatorFactory : public QObject, public ICalculatorFactory
{
public:
    SimpleFakeCalculatorFactory() {}

    virtual ICalculator* Create(ITransport *transport, QObject *parent) override;
};

}
