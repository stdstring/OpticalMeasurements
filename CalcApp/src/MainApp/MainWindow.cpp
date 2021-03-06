#include <QMainWindow>
#include <QString>
#include <QTextStream>
#include <QWidget>

#include <algorithm>
#include <iterator>

#include "Common/CommonDefs.h"
#include "Common/Logger/ILogger.h"
#include "Common/ActionsConfig.h"
#include "Common/ExceptionData.h"
#include "Common/IAction.h"
#include "Common/MainConfig.h"
#include "Common/ServiceLocator.h"
#include "ActionManager.h"
#include "ResultProcessor.h"
#include "StateManager.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

namespace CalcApp
{

namespace
{

QString CreateItemText(QString const &name, QString const &suffix)
{
    QString descriptor;
    QTextStream(&descriptor) << name << " " << suffix;
    return descriptor;
}

}

MainWindow::MainWindow(ServiceLocatorPtr serviceLocator, QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _serviceLocator(serviceLocator),
    _actionManager(new ActionManager(serviceLocator, this)),
    _stateManager(nullptr),
    _resultProcessor(new ResultProcessor(serviceLocator.get()->GetConfig(), serviceLocator.get()->GetLogger(), this))
{
    _ui->setupUi(this);
    _stateManager = new StateManager(_ui->ActionChainsComboBox,
                                     _ui->CreateButton,
                                     _ui->RunButton,
                                     _ui->StopButton,
                                     _ui->ResultButton,
                                     _ui->ClearButton,
                                     this);
    QStringList actionChainList;
    MainConfigPtr config = serviceLocator.get()->GetConfig();
    std::transform(config.get()->Actions.Chains.cbegin(),
                   config.get()->Actions.Chains.cend(),
                   std::back_inserter(actionChainList),
                   [](ActionChainDef const &chain){ return chain.Name; });
    _ui->ActionChainsComboBox->addItems(actionChainList);
    // signals
    QObject::connect(_ui->CreateButton, &QPushButton::clicked, this, &MainWindow::CreateButtonClick);
    QObject::connect(_ui->RunButton, &QPushButton::clicked, this, &MainWindow::RunButtonClick);
    QObject::connect(_ui->StopButton, &QPushButton::clicked, this, &MainWindow::StopButtonClick);
    QObject::connect(_ui->ResultButton, &QPushButton::clicked, this, &MainWindow::ResultButtonClick);
    QObject::connect(_ui->ClearButton, &QPushButton::clicked, this, &MainWindow::ClearButtonClick);
    QObject::connect(_actionManager, &ActionManager::ActionRunning, this, &MainWindow::ProcessActionRunning);
    QObject::connect(_actionManager, &ActionManager::ActionCompleted, this, &MainWindow::ProcessActionCompleted);
    QObject::connect(_actionManager, &ActionManager::ActionFailed, this, &MainWindow::ProcessActionFailed);
    QObject::connect(_actionManager, &ActionManager::ActionAborted, this, &MainWindow::ProcessActionAborted);
    QObject::connect(_actionManager, &ActionManager::ActionChainCompleted, this, &MainWindow::ProcessActionChainCompleted);
    QObject::connect(_actionManager, &ActionManager::ActionChainAborted, this, &MainWindow::ProcessActionChainAborted);
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::CreateButtonClick()
{
    QString chainName = _ui->ActionChainsComboBox->currentText();
    QStringList actions = _actionManager->Create(chainName);
    _actions = actions;
    QStringList dest;
    std::transform(actions.cbegin(), actions.cend(), std::back_inserter(dest), [](QString const &name) { return CreateItemText(name, "[not started]"); });
    _ui->ActionsListWidget->addItems(dest);
    _stateManager->ChangeState(MainAppState::CHAIN_CREATED);
}

void MainWindow::RunButtonClick()
{
    _actionManager->Run();
    _stateManager->ChangeState(MainAppState::CHAIN_RUNNING);
}

void MainWindow::StopButtonClick()
{
    _actionManager->Stop();
}

void MainWindow::ClearButtonClick()
{
    _actionManager->Clear();
    _actions.clear();
    _ui->ActionsListWidget->clear();
    _stateManager->ChangeState(MainAppState::INIT);
}

void MainWindow::ResultButtonClick()
{
    ActionChainDefPtr chain = _actionManager->GetCurrentChainDef();
    _resultProcessor->ShowResult(chain);
}

void MainWindow::ProcessActionRunning(QString name)
{
    // TODO (std_string) : move into common method
    int actionIndex = _actions.QList<QString>::indexOf(name);
    _ui->ActionsListWidget->item(actionIndex)->setText(CreateItemText(_actions[actionIndex], "[running]"));
}

void MainWindow::ProcessActionCompleted(QString name)
{
    // TODO (std_string) : move into common method
    int actionIndex = _actions.QList<QString>::indexOf(name);
    _ui->ActionsListWidget->item(actionIndex)->setText(CreateItemText(_actions[actionIndex], "[completed]"));
}

void MainWindow::ProcessActionAborted(QString name)
{
    // TODO (std_string) : move into common method
    int actionIndex = _actions.QList<QString>::indexOf(name);
    _ui->ActionsListWidget->item(actionIndex)->setText(CreateItemText(_actions[actionIndex], "[aborted]"));
}

void MainWindow::ProcessActionFailed(QString name, ExceptionData exception)
{
    Q_UNUSED(exception)
    // TODO (std_string) : move into common method
    // TODO (std_string) : think about processing of exception
    int actionIndex = _actions.QList<QString>::indexOf(name);
    _ui->ActionsListWidget->item(actionIndex)->setText(CreateItemText(_actions[actionIndex], "[failed]"));
}

void MainWindow::ProcessActionChainCompleted()
{
    _stateManager->ChangeState(MainAppState::CHAIN_COMPLETED);
}

void MainWindow::ProcessActionChainAborted()
{
    _stateManager->ChangeState(MainAppState::CHAIN_ABORTED);
}

}
