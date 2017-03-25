#include <QAbstractButton>

#include "StateManager.h"

namespace CalcApp
{

StateManager::StateManager(QComboBox *actionChainsComboBox,
                           QAbstractButton *createButton,
                           QAbstractButton *runButton,
                           QAbstractButton *stopButton,
                           QAbstractButton *resultButton,
                           QAbstractButton *clearButton,
                           QObject *parent) :
    QObject(parent),
    _actionChainsComboBox(actionChainsComboBox),
    _createButton(createButton),
    _runButton(runButton),
    _stopButton(stopButton),
    _resultButton(resultButton),
    _clearButton(clearButton)
{
    ChangeState(MainAppState::INIT);
}

void StateManager::ChangeState(MainAppState state)
{
    // TODO (std_string) : use more functional style
    switch (state)
    {
        case MainAppState::INIT:
            Init();
            break;
        case MainAppState::CHAIN_CREATED:
            ChainCreated();
            break;
        case MainAppState::CHAIN_RUNNING:
            ChainRunning();
            break;
        case MainAppState::CHAIN_COMPLETED:
            ChainCompleted();
            break;
        case MainAppState::CHAIN_ABORTED:
            ChainAborted();
            break;
    }
    //_state = state;
}

void StateManager::Init()
{
    _actionChainsComboBox->setEnabled(true);
    _createButton->setEnabled(true);
    _runButton->setEnabled(false);
    _stopButton->setEnabled(false);
    _resultButton->setEnabled(false);
    _clearButton->setEnabled(false);
}

void StateManager::ChainCreated()
{
    _actionChainsComboBox->setEnabled(false);
    _createButton->setEnabled(false);
    _runButton->setEnabled(true);
    _stopButton->setEnabled(false);
    _resultButton->setEnabled(false);
    _clearButton->setEnabled(true);
}

void StateManager::ChainRunning()
{
    _actionChainsComboBox->setEnabled(false);
    _createButton->setEnabled(false);
    _runButton->setEnabled(false);
    _stopButton->setEnabled(true);
    _resultButton->setEnabled(false);
    _clearButton->setEnabled(false);
}

void StateManager::ChainCompleted()
{
    _actionChainsComboBox->setEnabled(false);
    _createButton->setEnabled(false);
    _runButton->setEnabled(false);
    _stopButton->setEnabled(false);
    _resultButton->setEnabled(true);
    _clearButton->setEnabled(true);
}

void StateManager::ChainAborted()
{
    _actionChainsComboBox->setEnabled(false);
    _createButton->setEnabled(false);
    _runButton->setEnabled(false);
    _stopButton->setEnabled(false);
    _resultButton->setEnabled(false);
    _clearButton->setEnabled(true);
}

}
