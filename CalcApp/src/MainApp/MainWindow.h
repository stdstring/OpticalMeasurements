#pragma once

#include <QMainWindow>
#include <QString>

#include "Common/ComponentStorage.h"
#include "Common/MainConfig.h"
#include "ActionManager.h"
#include "StateManager.h"

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
    MainWindow(MainConfig const &config, ComponentStorage const &storage, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ActionManager *_actionManager;
    StateManager *_stateManager;

private slots:
    /*// TODO (std_string) : think about name
    void ActionChainIndexChange(int index);*/
    void CreateButtonClick();
    void RunButtonClick();
    void StopButtonClick();
    void ResultButtonClick();
    void ProcessActionRunning(int index, QString const &name);
    void ProcessActionFinished(int index, QString const &name);
    void ProcessActionChainFinished();
};

}
