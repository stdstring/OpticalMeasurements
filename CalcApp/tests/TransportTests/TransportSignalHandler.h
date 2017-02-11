#pragma once

#include <QList>
#include <QObject>

#include "ITransport.h"
#include "Message.h"

namespace CalcApp
{

class TransportSignalHandler : public QObject
{
    Q_OBJECT
public:
    TransportSignalHandler(ITransport *transport, QObject *parent = nullptr);
    QList<Message> Messages;

private slots:
    void ProcessResponse(Message const &message);
    void ProcessData(Message const &message);
    void ProcessEvent(Message const &message);
};

}
