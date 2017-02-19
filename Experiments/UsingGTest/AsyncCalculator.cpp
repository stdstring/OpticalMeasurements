#include <QObject>
#include <QThread>

#include <iostream>

#include "gtest/gtest.h"

#include "AsyncCalculator.h"

AsyncCalculator::AsyncCalculator(unsigned long delay, QObject *parent) :
    QObject(parent),
    _delay(delay)
{
    QObject::connect(this, &AsyncCalculator::CalculationStarted, this, &AsyncCalculator::ProcessCalculation);
}

void AsyncCalculator::StartCalculation(int a, int b)
{
    emit CalculationStarted(a, b);
}

void AsyncCalculator::ProcessStart()
{
}

void AsyncCalculator::ProcessFinish()
{
}

void AsyncCalculator::ProcessCalculation(int a, int b)
{
    QThread::msleep(_delay);
    emit CalculationCompleted(a + b);
}

AsyncCalculatorRunner::AsyncCalculatorRunner(unsigned long delay, QObject *parent) :
    QObject(parent),
    _calculator(new AsyncCalculator(delay, this)),
    _thread(new QThread(this))
{
    QObject::connect(_thread, &QThread::started, _calculator, &AsyncCalculator::ProcessStart);
    QObject::connect(_thread, &QThread::finished, _calculator, &AsyncCalculator::ProcessFinish);
    QObject::connect(_calculator, &AsyncCalculator::CalculationCompleted, this, &AsyncCalculatorRunner::CalculationCompleted);
}

void AsyncCalculatorRunner::Start()
{
    _thread->start();
}

void AsyncCalculatorRunner::Finish()
{
    _thread->exit();
}

void AsyncCalculatorRunner::StartCalculation(int a, int b)
{
    _calculator->StartCalculation(a, b);
}

void AsyncCalulatorResultChecker::Check(AsyncCalculatorRunner *runner, int a, int b, int expectedResult)
{
    AsyncCalulatorResultChecker checker(QThread::currentThread(), runner, a, b, expectedResult);
    QThread thread;
    runner->moveToThread(&thread);
    checker.moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, &checker, &AsyncCalulatorResultChecker::ProcessStart);
    QObject::connect(&thread, &QThread::finished, &checker, &AsyncCalulatorResultChecker::ProcessFinish);
    thread.start();
    thread.wait();
}

AsyncCalulatorResultChecker::AsyncCalulatorResultChecker(QThread *initThread, AsyncCalculatorRunner *runner, int a, int b, int expectedResult) :
    QObject(nullptr),
    _runner(runner),
    _a(a),
    _b(b),
    _expectedResult(expectedResult),
    _initThread(initThread)
{
    QObject::connect(_runner, &AsyncCalculatorRunner::CalculationCompleted, this, &AsyncCalulatorResultChecker::ProcessResult);
}

void AsyncCalulatorResultChecker::ProcessStart()
{
    _runner->StartCalculation(_a, _b);
}

void AsyncCalulatorResultChecker::ProcessFinish()
{
    this->moveToThread(_initThread);
    _runner->moveToThread(_initThread);
}

void AsyncCalulatorResultChecker::ProcessResult(int result)
{
    EXPECT_EQ(_expectedResult, result);
    QThread::currentThread()->exit();
}
