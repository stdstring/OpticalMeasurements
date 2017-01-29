#pragma once

#include <QList>
#include <QObject>

#include "ISimpleCalculator.h"

class ComplexCalculator : public QObject
{
    Q_OBJECT
public:
    explicit ComplexCalculator(ISimpleCalculator *simpleCalculator, QObject *parent = 0);
    int CalcA(int a, int b, int c);

    QList<int> OddResults;

private:
    ISimpleCalculator *_simpleCalculator;

private slots:
    void InfoOddResult(int value);
};
