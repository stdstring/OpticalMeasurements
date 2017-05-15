#pragma once

#include <QMainWindow>
#include <QThread>

#include <memory>

#include "CustomExceptionData.h"
#include "CustomMessageData.h"
#include "Processor.h"

namespace Ui
{
class MainWindow;
}

namespace CustomSignalData
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Processor> _processor;
    std::shared_ptr<QThread> _thread;

private slots:
    void ProcessFirstSignal(CustomMessageData const &data);
    void ProcessSecondSignal(CustomExceptionData const &data);
};

}
