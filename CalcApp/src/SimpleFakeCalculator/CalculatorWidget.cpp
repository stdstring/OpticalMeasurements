#include "CalculatorWidget.h"
#include "ui_CalculatorWidget.h"

CalculatorWidget::CalculatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatorWidget)
{
    ui->setupUi(this);
}

CalculatorWidget::~CalculatorWidget()
{
    delete ui;
}
