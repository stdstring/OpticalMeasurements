#pragma once

#include <QMainWindow>

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
};

}
