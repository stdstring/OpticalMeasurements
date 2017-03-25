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
    /*QObject::connect(ui->ActionChainsComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::ActionChainIndexChange);*/
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

/*void MainWindow::ActionChainIndexChange(int index)
{
}*/

void MainWindow::CreateButtonClick()
{
    QString chainName = ui->ActionChainsComboBox->currentText();
    _actionManager->Clear();
    QStringList actions = _actionManager->Create(chainName, this);
    QStringList dest;
    std::transform(actions.cbegin(), actions.cend(), std::back_inserter(dest), [](QString const &name)
    {
        QString descriptor;
        QTextStream(&descriptor) << name << " [not started]";
        return descriptor;
    });
    ui->ActionsListWidget->clear();
    ui->ActionsListWidget->addItems(dest);
    _stateManager->ChangeState(MainAppState::CHAIN_CREATED_STATE);
}

void MainWindow::RunButtonClick()
{
    _actionManager->Run();
    _stateManager->ChangeState(MainAppState::CHAIN_RUNNING_STATE);
}

void MainWindow::StopButtonClick()
{
    _actionManager->Stop();
    _stateManager->ChangeState(MainAppState::CHAIN_FINISHED_STATE);
}

void MainWindow::ResultButtonClick()
{
    // TODO (std_string) : extract data from context
    QMessageBox resultInfo;
    resultInfo.setText("There is the result of the execution");
    resultInfo.exec();
}

void MainWindow::ProcessActionRunning(int index, QString const &name)
{
    QString descriptor;
    QTextStream(&descriptor) << name << " [running]";
    ui->ActionsListWidget->item(index)->setText(descriptor);
}

void MainWindow::ProcessActionFinished(int index, QString const &name)
{
    QString descriptor;
    QTextStream(&descriptor) << name << " [completed]";
    ui->ActionsListWidget->item(index)->setText(descriptor);
}

void MainWindow::ProcessActionChainFinished()
{
    _stateManager->ChangeState(MainAppState::CHAIN_FINISHED_STATE);
}

}
