#pragma once

#include <QMainWindow>
#include <QWidget>

namespace Ui
{

class MainWindow;

}

namespace OpenGLDemo
{

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *child, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void ProcessOpenFile();
};

}
