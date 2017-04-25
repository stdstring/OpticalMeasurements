#pragma once

#include <QObject>
#include <QString>

#include <exception>

#include "Context.h"

namespace CalcApp
{

class IAction : public QObject
{
    Q_OBJECT
public:
    explicit IAction(QObject *parent = nullptr) : QObject(parent) {}

    virtual QString GetName() = 0;
    virtual void Run(Context &context) = 0;
    /*virtual void StartAction(Context &context) = 0;*/

signals:
    void DataCompleted(QString const &key);
    void ErrorOccured(std::exception_ptr exception);
    /*void ActionFinished();*/
};

}
