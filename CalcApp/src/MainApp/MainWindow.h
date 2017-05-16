#pragma once

#include <QMainWindow>
#include <QString>
#include <QStringList>

#include "Common/IAction.h"
#include "Common/ServiceLocator.h"
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
    MainWindow(ServiceLocator const &serviceLocator, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    ActionManager *_actionManager;
    StateManager *_stateManager;
    QStringList _actions;

private slots:
    void CreateButtonClick();
    void RunButtonClick();
    void StopButtonClick();
    void ResultButtonClick();
    void ClearButtonClick();
    void ProcessActionRunning(QString name);
    void ProcessActionCompleted(QString name);
    void ProcessActionAborted(QString name);
    void ProcessActionFailed(QString name, ExceptionData exception);
    void ProcessActionChainCompleted();
    void ProcessActionChainAborted();
};

}
