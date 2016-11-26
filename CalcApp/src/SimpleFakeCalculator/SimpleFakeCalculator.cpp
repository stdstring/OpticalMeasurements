#include <QObject>
#include <QWidget>

#include "../CommonLib/ITransport.h"
#include "SimpleFakeCalculator.h"

namespace CalcApp
{

SimpleFakeCalculator::SimpleFakeCalculator(ITransport *transport, QObject *parent) : QObject(parent)
{
}

QWidget* SimpleFakeCalculator::CreateCalculatorWidget(QWidget *parent)
{
    return nullptr;
}

}
