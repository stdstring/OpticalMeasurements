#include <QObject>

#include "../CommonLib/ICalculator.h"
#include "../CommonLib/ICalculatorFactory.h"
#include "../CommonLib/ITransport.h"
#include "SimpleFakeCalculator.h"
#include "SimpleFakeCalculatorFactory.h"

namespace CalcApp
{

ICalculator* SimpleFakeCalculatorFactory::Create(ITransport *transport, QObject *parent)
{
    return new SimpleFakeCalculator(transport, parent);
}

}
