#include <QEventLoop>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QTextStream>
#include <QThread>
#include <QWidget>

#include "MainWindow.h"
#include "ui_MainWindow.h"

QString CreateInfo(QString const &prefix)
{
    QString notification;
    QTextStream stream(&notification);
    stream << prefix << QThread::currentThreadId();
    return notification;
}

Calculator::Calculator()
{
    QObject::connect(this, &Calculator::StartCalculation, this, &Calculator::ProcessCalculation);
}

void Calculator::Calculate()
{
    emit StartCalculation();
}

void Calculator::ProcessCalculation()
{
    QThread::sleep(10);
    emit Notify(CreateInfo("Processed in thread with id = "));
}

CalculatorThread::CalculatorThread(Calculator *calculator, QObject *parent) : QThread(parent), _calculator(calculator)
{
}

void CalculatorThread::run()
{
    emit Notify(CreateInfo("run in thread with id = "));
    QThread::exec();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _calculator(new Calculator()),
    _calculatorThread(new CalculatorThread(_calculator, this))
{
    _ui->setupUi(this);
    _ui->ResultWidget->addItem(CreateInfo("Main thread id = "));
    QObject::connect(_ui->ProcessButton, &QPushButton::clicked, this, &MainWindow::ProcessButtonClick);
    QObject::connect(_calculator, &Calculator::Notify, this, &MainWindow::ProcessNotification);
    QObject::connect(_calculatorThread, &CalculatorThread::Notify, this, &MainWindow::ProcessNotification);
    _calculator->moveToThread(_calculatorThread);
    _calculatorThread->start();
}

MainWindow::~MainWindow()
{
    delete _ui;
    _calculatorThread->quit();
    delete _calculator;
}

void MainWindow::ProcessButtonClick()
{
    _calculator->Calculate();
}

void MainWindow::ProcessNotification(QString const &notification)
{
    _ui->ResultWidget->addItem(notification);
}
