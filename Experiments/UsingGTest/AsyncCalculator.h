#pragma once

#include <QObject>
#include <QThread>

class AsyncCalculator : public QObject
{
    Q_OBJECT
public:
    explicit AsyncCalculator(unsigned long delay = 1000, QObject *parent = 0);
    void StartCalculation(int a, int b);

private:
    unsigned long _delay;

signals:
    void CalculationCompleted(int result);
    void CalculationStarted(int a, int b);

public slots:
    void ProcessStart();
    void ProcessFinish();

private slots:
    void ProcessCalculation(int a, int b);
};

class AsyncCalculatorRunner : public QObject
{
    Q_OBJECT
public:
    explicit AsyncCalculatorRunner(unsigned long delay = 1000, QObject *parent = 0);
    void Start();
    void Finish();
    void StartCalculation(int a, int b);

private:
    AsyncCalculator *_calculator;
    QThread *_thread;

signals:
    void CalculationCompleted(int result);
};

class AsyncCalulatorResultChecker : public QObject
{
    Q_OBJECT
public:
    AsyncCalulatorResultChecker(QThread *initThread, AsyncCalculatorRunner *runner, int a, int b, int expectedResult);
    static void Check(AsyncCalculatorRunner *runner, int a, int b, int expectedResult);

private:
    AsyncCalculatorRunner *_runner;
    int _a;
    int _b;
    int _expectedResult;
    QThread *_initThread;

private slots:
    void ProcessStart();
    void ProcessFinish();
    void ProcessResult(int result);
};
