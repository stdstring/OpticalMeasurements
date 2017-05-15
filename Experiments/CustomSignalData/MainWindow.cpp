#include <QMessageBox>
#include <QMetaType>
#include <QPushButton>
#include <QString>
#include <QTextStream>

#include <exception>
#include <stdexcept>

#include "CustomExceptionData.h"
#include "CustomMessageData.h"
#include "MainWindow.h"
#include "Processor.h"
#include "ui_mainwindow.h"

namespace CustomSignalData
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _processor(new Processor()),
    _thread(new QThread())
{
    ui->setupUi(this);
    QObject::connect(ui->FirstButton, &QPushButton::clicked, _processor.get(), &Processor::ProcessFirst);
    QObject::connect(ui->SecondButton, &QPushButton::clicked, _processor.get(), &Processor::ProcessSecond);
    QObject::connect(_processor.get(), &Processor::FirstSignal, this, &MainWindow::ProcessFirstSignal);
    QObject::connect(_processor.get(), &Processor::SecondSignal, this, &MainWindow::ProcessSecondSignal);
    QObject::connect(_thread.get(), &QThread::started, _processor.get(), &Processor::ProcessStart);
    QObject::connect(_thread.get(), &QThread::finished, _processor.get(), &Processor::ProcessFinish);
    _processor.get()->moveToThread(_thread.get());
    _thread.get()->start();
}

MainWindow::~MainWindow()
{
    _thread.get()->exit(0);
    _thread.get()->wait();
    delete ui;
}

void MainWindow::ProcessFirstSignal(CustomMessageData const &data)
{
    QString value;
    QTextStream(&value) << data.Value1 << " " << data.Value2;
    QMessageBox::information(this, "info", value);
}

void MainWindow::ProcessSecondSignal(CustomExceptionData const &data)
{
    Q_UNUSED(data)
    QMessageBox::information(this, "info", "exception occur");
}

}
