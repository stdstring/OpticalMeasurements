#include <QObject>
#include <QWidget>

#include "../CommonLib/ITransport.h"
#include "SimpleFakeCalculator.h"

namespace CalcApp
{

SimpleFakeCalculator::SimpleFakeCalculator(QObject *parent, ITransport *transport) : QObject(parent)
{
}

QWidget* SimpleFakeCalculator::CreateCalculatorWidget(QWidget *parent)
{
    return nullptr;
}

}
