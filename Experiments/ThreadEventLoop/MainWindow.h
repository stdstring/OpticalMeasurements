#pragma once

#include <QMainWindow>
#include <QObject>
#include <QThread>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class Calculator : public QObject
{
    Q_OBJECT
public:
    Calculator();
    void Calculate();

signals:
    void StartCalculation();
    void Notify(QString const &notification);

private slots:
    void ProcessCalculation();
};

class CalculatorThread : public QThread
{
    Q_OBJECT
public:
    CalculatorThread(Calculator *calculator, QObject *parent);

protected:
    virtual void run() override;

private:
    Calculator *_calculator;

signals:
    void Notify(QString const &notification);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    Calculator *_calculator;
    CalculatorThread *_calculatorThread;

private slots:
    void ProcessButtonClick();
    void ProcessNotification(QString const &notification);
};

