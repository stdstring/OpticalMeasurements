#include <QObject>
#include <QWidget>

#include "SimpleFakeCalculator.h"

namespace CalcApp
{

SimpleFakeCalculator::SimpleFakeCalculator(QObject *parent) : QObject(parent)
{
}

QWidget* SimpleFakeCalculator::CreateCalculatorWidget(QWidget *parent)
{
    return nullptr;
}

}
