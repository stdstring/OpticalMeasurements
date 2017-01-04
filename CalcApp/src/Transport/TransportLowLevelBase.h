#pragma once

#include <QObject>

#include "Message.h"

namespace CalcApp
{

class TransportLowLevelBase : public QObject
{
    Q_OBJECT
public:
    TransportLowLevelBase(QObject *parent) : QObject(parent) {}
    virtual Message Exchange(Message const &message) = 0;

signals:
    void DataReceived(Message const &message);
    void EventReceived(Message const &message);
};

}
