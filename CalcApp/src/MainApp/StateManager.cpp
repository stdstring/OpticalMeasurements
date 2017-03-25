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
    _state = state;
}

void StateManager::Init()
{
    _createButton->setEnabled(true);
    _runButton->setEnabled(false);
    _stopButton->setEnabled(false);
    _resultButton->setEnabled(false);
}

void StateManager::ChainCreated()
{
    _createButton->setEnabled(true);
    _runButton->setEnabled(true);
    _stopButton->setEnabled(false);
    _resultButton->setEnabled(false);
}

void StateManager::ChainRunning()
{
    _createButton->setEnabled(false);
    _runButton->setEnabled(false);
    _stopButton->setEnabled(true);
    _resultButton->setEnabled(false);
}

void StateManager::ChainCompleted()
{
    _createButton->setEnabled(true);
    _runButton->setEnabled(false);
    _stopButton->setEnabled(false);
    _resultButton->setEnabled(true);

}

void StateManager::ChainAborted()
{
    _createButton->setEnabled(true);
    _runButton->setEnabled(false);
    _stopButton->setEnabled(false);
    _resultButton->setEnabled(false);

}

}
