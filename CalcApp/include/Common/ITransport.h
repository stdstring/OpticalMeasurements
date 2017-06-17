#pragma once

#include <QObject>

#include "CommonDefs.h"
#include "Message.h"

namespace CalcApp
{

class ITransport : public QObject
{
    Q_OBJECT
public:
    explicit ITransport(QObject *parent = nullptr) : QObject(parent) {}
    virtual void Connect() = 0;
    virtual void Send(MessagePtr message) = 0;
    virtual void Disconnect() = 0;

signals:
    void ResponseReceived(MessagePtr message);
    void DataReceived(MessagePtr message);
    void DataProcessFailed();
    void EventReceived(MessagePtr message);

};

}
