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
    virtual void Connect() = 0;
    virtual void Send(Message const &message) = 0;

signals:
    void ResponseReceived(Message const &message);
    void DataReceived(Message const &message);
    void EventReceived(Message const &message);
};

}
