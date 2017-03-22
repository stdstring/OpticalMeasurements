#pragma once

#include <QAbstractButton>
#include <QObject>

namespace CalcApp
{

enum MainAppState { INIT_STATE, CHAIN_CREATED_STATE, CHAIN_RUNNING_STATE, CHAIN_FINISHED_STATE };

class StateManager : public QObject
{
public:
    StateManager(QAbstractButton *createButton,
                 QAbstractButton *runButton,
                 QAbstractButton *stopButton,
                 QAbstractButton *resultButton,
                 QObject *parent = nullptr);
    void ChangeState(MainAppState state);

private:
    void SetInitState();
    void SetChainCreatedState();
    void SetChainRunningState();
    void SetChainFinishedState();

    MainAppState _state;
    QAbstractButton *_createButton;
    QAbstractButton *_runButton;
    QAbstractButton *_stopButton;
    QAbstractButton *_resultButton;
};

}
