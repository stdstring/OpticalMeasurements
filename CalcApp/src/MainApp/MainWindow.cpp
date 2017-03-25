#include <QMainWindow>
#include <QMessageBox>
#include <QStringList>
#include <QTextStream>

#include <algorithm>
#include <iterator>

#include "Common/ActionsConfig.h"
#include "Common/ComponentStorage.h"
#include "Common/MainConfig.h"
#include "ActionManager.h"
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

MainWindow::MainWindow(MainConfig const &config, ComponentStorage const &storage, QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _actionManager(new ActionManager(config, storage, this)),
    _stateManager(nullptr),
    _currentActionIndex(-1)
{
    _ui->setupUi(this);
    _stateManager = new StateManager(_ui->CreateButton,
                                     _ui->RunButton,
                                     _ui->StopButton,
                                     _ui->ResultButton,
                                     _ui->ClearButton,
                                     this);
    QStringList actionChainList;
    std::transform(config.Actions.Chains.cbegin(),
                   config.Actions.Chains.cend(),
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
    QStringList actions = _actionManager->Create(chainName, this);
    _currentActionIndex = 0;
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
    _currentActionIndex = -1;
    _ui->ActionsListWidget->clear();
    _stateManager->ChangeState(MainAppState::INIT);
}

void MainWindow::ResultButtonClick()
{
    // TODO (std_string) : extract data from context
    QMessageBox resultInfo;
    resultInfo.setText("There is the result of the execution");
    resultInfo.exec();
}

void MainWindow::ProcessActionRunning(int index)
{
    _ui->ActionsListWidget->item(index)->setText(CreateItemText(_actions[index], "[running]"));
    _currentActionIndex = index;
}

void MainWindow::ProcessActionCompleted(int index)
{
    _ui->ActionsListWidget->item(index)->setText(CreateItemText(_actions[index], "[completed]"));
    _currentActionIndex = index + 1;
}

void MainWindow::ProcessActionFailed(int index)
{
    _ui->ActionsListWidget->item(index)->setText(CreateItemText(_actions[index], "[failed]"));
    _currentActionIndex = index + 1;
}

void MainWindow::ProcessActionChainCompleted()
{
    _stateManager->ChangeState(MainAppState::CHAIN_COMPLETED);
}

void MainWindow::ProcessActionChainAborted()
{
    _stateManager->ChangeState(MainAppState::CHAIN_ABORTED);
    // TODO (std_string) : think about using some of algorithms
    for (int index = _currentActionIndex; index < _actions.size(); ++index)
    {
        _ui->ActionsListWidget->item(index)->setText(CreateItemText(_actions[index], "[aborted]"));
    }
}

}
