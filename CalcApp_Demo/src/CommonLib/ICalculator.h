#pragma once

#include <QWidget>

namespace CalcApp
{

class ICalculator
{
public:
    virtual QWidget* CreateCalculatorWidget(QWidget *parent) = 0;
    virtual ~ICalculator() { /* do nothing */ }
};

}
