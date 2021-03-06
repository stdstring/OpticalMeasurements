#pragma once

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

namespace CalcApp
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString const &header, QString const &data, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

}
