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

public slots:
    void Started();

private slots:
    void ProcessCalculation();
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
    QThread *_calculatorThread;

private slots:
    void ProcessButtonClick();
    void ProcessNotification(QString const &notification);
};

