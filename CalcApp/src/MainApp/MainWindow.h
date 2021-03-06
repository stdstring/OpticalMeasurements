#pragma once

#include <QMainWindow>
#include <QString>
#include <QStringList>

#include "Common/CommonDefs.h"
#include "Common/ExceptionData.h"
#include "ActionManager.h"
#include "ResultProcessor.h"
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
    MainWindow(ServiceLocatorPtr serviceLocator, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    ServiceLocatorPtr _serviceLocator;
    ActionManager *_actionManager;
    StateManager *_stateManager;
    QStringList _actions;
    ResultProcessor *_resultProcessor;

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
