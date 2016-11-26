#include <QObject>
#include <QWidget>

#include "../CommonLib/ITransport.h"
#include "CalculatorWidget.h"
#include "SimpleFakeCalculator.h"

namespace CalcApp
{

SimpleFakeCalculator::SimpleFakeCalculator(ITransport *transport, QObject *parent) : QObject(parent), _transport(transport)
{
}

QWidget* SimpleFakeCalculator::CreateCalculatorWidget(QWidget *parent)
{
    return new CalculatorWidget(_transport, parent);
}

}
