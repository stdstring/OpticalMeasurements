#pragma once

#include <QWidget>

#include "../CommonLib/ITransport.h"

namespace Ui
{
class CalculatorWidget;
}

class CalculatorWidget : public QWidget
{
    Q_OBJECT

public:
    CalculatorWidget(CalcApp::ITransport *transport, QWidget *parent);
    ~CalculatorWidget();

private slots:
    void RunHandler();

private:
    Ui::CalculatorWidget *ui;
    CalcApp::ITransport *_transport;
};
