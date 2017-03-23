#include <QMainWindow>
#include <QStringList>

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

MainWindow::MainWindow(MainConfig const &config, ComponentStorage const &storage, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _actionManager(new ActionManager(config, storage, this)),
    _stateManager(nullptr)
{
    ui->setupUi(this);
    _stateManager = new StateManager(ui->CreateButton, ui->RunButton, ui->StopButton, ui->ResultButton, this);
    QStringList actionChainList;
    std::transform(config.Actions.Chains.cbegin(),
                   config.Actions.Chains.cend(),
                   std::back_inserter(actionChainList),
                   [](ActionChainDef const &chain){ return chain.Name; });
    ui->ActionChainsComboBox->addItems(actionChainList);
    // signals
    QObject::connect(ui->CreateButton, &QPushButton::clicked, this, &MainWindow::CreateButtonClick);
    QObject::connect(ui->RunButton, &QPushButton::clicked, this, &MainWindow::RunButtonClick);
    QObject::connect(ui->StopButton, &QPushButton::clicked, this, &MainWindow::StopButtonClick);
    QObject::connect(ui->ResultButton, &QPushButton::clicked, this, &MainWindow::ResultButtonClick);
    QObject::connect(_actionManager, &ActionManager::ActionRunning, this, &MainWindow::ProcessActionRunning);
    QObject::connect(_actionManager, &ActionManager::ActionFinished, this, &MainWindow::ProcessActionFinished);
    QObject::connect(_actionManager, &ActionManager::ActionChainFinished, this, &MainWindow::ProcessActionChainFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateButtonClick()
{
}

void MainWindow::RunButtonClick()
{
}

void MainWindow::StopButtonClick()
{
}

void MainWindow::ResultButtonClick()
{
}

void MainWindow::ProcessActionRunning(int index, QString const &name)
{
}

void MainWindow::ProcessActionFinished(int index, QString const &name)
{
}

void MainWindow::ProcessActionChainFinished()
{
}

}
