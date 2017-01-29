#pragma once

#include <QObject>

class Calculator : public QObject
{
    Q_OBJECT
public:
    explicit Calculator(QObject *parent = 0);
    int Add(int left, int right);
    int Sub(int left, int right);
};
