#pragma once

#include <QObject>
#include <QWidget>

#include "../CommonLib/ICalculator.h"
#include "../CommonLib/ITransport.h"

namespace CalcApp
{

class SimpleFakeCalculator : public QObject, public ICalculator
{
public:
    SimpleFakeCalculator(ITransport *transport, QObject *parent);

    virtual QWidget* CreateCalculatorWidget(QWidget *parent) override;
};

}
