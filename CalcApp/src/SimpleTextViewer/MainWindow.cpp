#include "MainWindow.h"
#include "ui_MainWindow.h"

namespace CalcApp
{

MainWindow::MainWindow(QString const &header, QString const &data, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->TextViewer->setPlainText(data);
    setWindowTitle(header);
    QObject::connect(ui->ActionExit, &QAction::triggered, this, [this](bool){ close(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

}
