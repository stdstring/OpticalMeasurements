#pragma once

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

struct DataItem
{
public:
    QString item;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void ProcessButtonClick();
    void ProcessData(DataItem data);

signals:
    void Process(DataItem data);
};
