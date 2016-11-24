#pragma once

#include <QObject>
#include <QWidget>
#include <QtPlugin>

#include "../CommonLib/ICalculator.h"
#include "../CommonLib/ITransport.h"

namespace CalcApp
{

class SimpleFakeCalculator : public QObject, ICalculator
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::ICalculator)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.ICalculator" FILE "SimpleFakeCalculator.json")
public:
    explicit SimpleFakeCalculator(QObject *parent, ITransport *transport);

    virtual QWidget* CreateCalculatorWidget(QWidget *parent) override;
};

}
