#include <QObject>

#include "../CommonLib/ICalculator.h"
#include "../CommonLib/ICalculatorFactory.h"
#include "../CommonLib/ITransport.h"
#include "SimpleFakeCalculatorFactory.h"

namespace CalcApp
{

ICalculator* SimpleFakeCalculatorFactory::Create(ITransport *transport, QObject *parent)
{

}

}
