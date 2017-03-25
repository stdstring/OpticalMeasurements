#pragma once

#include <QAbstractButton>
#include <QObject>

namespace CalcApp
{

enum MainAppState { INIT, CHAIN_CREATED, CHAIN_RUNNING, CHAIN_COMPLETED, CHAIN_ABORTED };

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
    void Init();
    void ChainCreated();
    void ChainRunning();
    void ChainCompleted();
    void ChainAborted();

    MainAppState _state;
    QAbstractButton *_createButton;
    QAbstractButton *_runButton;
    QAbstractButton *_stopButton;
    QAbstractButton *_resultButton;
};

}
