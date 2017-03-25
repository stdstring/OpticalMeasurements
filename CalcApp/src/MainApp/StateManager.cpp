#include <QAbstractButton>

#include "StateManager.h"

namespace CalcApp
{

StateManager::StateManager(QAbstractButton *createButton,
                           QAbstractButton *runButton,
                           QAbstractButton *stopButton,
                           QAbstractButton *resultButton,
                           QObject *parent) :
    QObject(parent),
    _createButton(createButton),
    _runButton(runButton),
    _stopButton(stopButton),
    _resultButton(resultButton)
{
    ChangeState(MainAppState::INIT_STATE);
}

void StateManager::ChangeState(MainAppState state)
{
    // TODO (std_string) : use more functional style
    switch (state)
    {
        case MainAppState::INIT_STATE:
            SetInitState();
            break;
        case MainAppState::CHAIN_CREATED_STATE:
            SetChainCreatedState();
            break;
        case MainAppState::CHAIN_RUNNING_STATE:
            SetChainRunningState();
            break;
        case MainAppState::CHAIN_FINISHED_STATE:
            SetChainFinishedState();
            break;
    }
    _state = state;
}

void StateManager::SetInitState()
{
    _createButton->setEnabled(true);
    _runButton->setEnabled(false);
    _stopButton->setEnabled(false);
    _resultButton->setEnabled(false);
}

void StateManager::SetChainCreatedState()
{
    _createButton->setEnabled(true);
    _runButton->setEnabled(true);
    _stopButton->setEnabled(false);
    _resultButton->setEnabled(false);
}

void StateManager::SetChainRunningState()
{
    _createButton->setEnabled(false);
    _runButton->setEnabled(false);
    _stopButton->setEnabled(true);
    _resultButton->setEnabled(false);
}

void StateManager::SetChainFinishedState()
{
    _createButton->setEnabled(true);
    _runButton->setEnabled(false);
    _stopButton->setEnabled(false);
    _resultButton->setEnabled(true);
}

}
