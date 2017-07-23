#include "MainWindow.h"
#include "ui_MainWindow.h"

namespace OpenGLDemo
{

MainWindow::MainWindow(QWidget *child, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(child);
}

MainWindow::~MainWindow()
{
    delete ui;
}

}
