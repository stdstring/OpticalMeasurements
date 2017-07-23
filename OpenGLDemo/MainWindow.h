#pragma once

#include <QMainWindow>

namespace Ui {
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
};

}
