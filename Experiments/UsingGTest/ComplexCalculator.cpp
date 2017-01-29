#include <QObject>

#include "ComplexCalculator.h"
#include "ISimpleCalculator.h"

ComplexCalculator::ComplexCalculator(ISimpleCalculator *simpleCalculator, QObject *parent) :
    QObject(parent),
    _simpleCalculator(simpleCalculator)
{
    QObject::connect(_simpleCalculator, &ISimpleCalculator::OddResult, this, &ComplexCalculator::InfoOddResult);
}

int ComplexCalculator::CalcA(int a, int b, int c)
{
    int value1 = _simpleCalculator->Add(a, b);
    int value2 = _simpleCalculator->Sub(b, c);
    int value3 = _simpleCalculator->Add(c, 3);
    int value4 = _simpleCalculator->Add(a, 2);
    return value1 + value2 + value3 + value4;
}

void ComplexCalculator::InfoOddResult(int value)
{
    OddResults.append(value);
}
