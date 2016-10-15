#pragma once

#include <QWidget>

namespace CalcApp
{

class ICalculator
{
public:
    virtual QWidget CreateCalculatorWidget() = 0;
};

}
