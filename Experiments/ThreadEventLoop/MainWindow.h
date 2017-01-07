#pragma once

#include <QMainWindow>
#include <QObject>
#include <QThread>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class Calculator : public QThread
{
    Q_OBJECT
public:
    Calculator(QObject *parent);
    void Calculate();

protected:
    virtual void run() override;

signals:
    void StartCalculation();
    void Notify(QString const &notification);

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

private slots:
    void ProcessButtonClick();
    void ProcessNotification(QString const &notification);
};

