#pragma once

#include <QObject>

class ISimpleCalculator : public QObject
{
    Q_OBJECT
public:
    explicit ISimpleCalculator(QObject *parent = 0) : QObject(parent) {}

    virtual int Add(int left, int right) = 0;
    virtual int Sub(int left, int right) = 0;

signals:
    void OddResult(int value);
};
