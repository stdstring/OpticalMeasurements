#include <QObject>
#include <QString>
#include <QStringList>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->ProcessButton, &QPushButton::clicked, this, &MainWindow::ProcessButtonClick);
    QObject::connect(this, &MainWindow::Process, this, &MainWindow::ProcessData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ProcessButtonClick()
{
    if (ui->InputEdit->text().isEmpty())
        return;
    QStringList items = ui->InputEdit->text().split(",", QString::SkipEmptyParts);
    foreach(QString item, items)
    {
        DataItem data;
        data.item = item;
        emit Process(data);
    }
    ui->InputEdit->clear();
}

void MainWindow::ProcessData(DataItem data)
{
    ui->OutputWidget->addItem(data.item);
}
