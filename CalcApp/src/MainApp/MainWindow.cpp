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
}

MainWindow::~MainWindow()
{
    delete ui;
}

}
