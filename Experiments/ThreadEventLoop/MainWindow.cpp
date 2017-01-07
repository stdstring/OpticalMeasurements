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

Calculator::Calculator(QObject *parent) : QThread(parent)
{
    QObject::connect(this, &Calculator::StartCalculation, this, &Calculator::ProcessCalculation);
}

void Calculator::Calculate()
{
    emit StartCalculation();
}

void Calculator::run()
{
    emit Notify(CreateInfo("run in thread with id = "));
    exec();
}

void Calculator::ProcessCalculation()
{
    QThread::sleep(10);
    emit Notify(CreateInfo("Processed in thread with id = "));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _calculator(new Calculator(this))
{
    _ui->setupUi(this);
    _ui->ResultWidget->addItem(CreateInfo("main tthread id = "));
    QObject::connect(_ui->ProcessButton, &QPushButton::clicked, this, &MainWindow::ProcessButtonClick);
    QObject::connect(_calculator, &Calculator::Notify, this, &MainWindow::ProcessNotification);
    _calculator->start();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::ProcessButtonClick()
{
    _calculator->Calculate();
}

void MainWindow::ProcessNotification(QString const &notification)
{
    _ui->ResultWidget->addItem(notification);
}
