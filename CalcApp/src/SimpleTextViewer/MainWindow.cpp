#include "MainWindow.h"
#include "ui_MainWindow.h"

namespace CalcApp
{

MainWindow::MainWindow(QString const &data, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->TextViewer->setPlainText(data);
}

MainWindow::~MainWindow()
{
    delete ui;
}

}
