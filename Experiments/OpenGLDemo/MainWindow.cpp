#include <QAction>
#include <QFileDialog>
#include <QList>
#include <QMainWindow>
#include <QWidget>

#include "MainWindow.h"
#include "OpenGLXYZWidget.h"
#include "ui_MainWindow.h"
#include "Vertex3D.h"
#include "XYZReader.h"

namespace OpenGLDemo
{

MainWindow::MainWindow(QWidget *child, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(child);
    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::ProcessOpenFile);
    QObject::connect(ui->actionExit, &QAction::triggered, this, [this](){ close(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ProcessOpenFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open XYZ source", ".", "XYZ source (*.xyz)");
    QList<Vertex3D> vertexList = ReadXYZSource(filename);
    dynamic_cast<OpenGLXYZWidget*>(this->centralWidget())->ShowData(vertexList);
}

}
