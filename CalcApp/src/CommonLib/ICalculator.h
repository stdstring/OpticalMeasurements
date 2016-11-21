#pragma once

#include <QtPlugin>
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

Q_DECLARE_INTERFACE(CalcApp::ICalculator, "com.stdstring.CalcApp.ICalculator")
