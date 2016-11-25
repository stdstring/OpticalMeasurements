#pragma once

#include <QObject>
#include <QWidget>

#include "../CommonLib/ICalculator.h"
#include "../CommonLib/ITransport.h"

namespace CalcApp
{

class SimpleFakeCalculator : public QObject, ICalculator
{
public:
    explicit SimpleFakeCalculator(QObject *parent, ITransport *transport);

    virtual QWidget* CreateCalculatorWidget(QWidget *parent) override;
};

}
