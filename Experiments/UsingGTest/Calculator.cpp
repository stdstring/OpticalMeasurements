#include <QObject>

#include "Calculator.h"

Calculator::Calculator(QObject *parent) : QObject(parent)
{
}

int Calculator::Add(int left, int right)
{
    return left + right;
}

int Calculator::Sub(int left, int right)
{
    return left - right;
}
