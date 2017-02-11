#include <QList>
#include <QObject>

#include "ITransport.h"
#include "Message.h"
#include "TransportSignalHandler.h"

namespace CalcApp
{

TransportSignalHandler::TransportSignalHandler(ITransport *transport, QObject *parent) :
    QObject(parent)
{
    QObject::connect(transport, &ITransport::ResponseReceived, this, &TransportSignalHandler::ProcessResponse);
    QObject::connect(transport, &ITransport::EventReceived, this, &TransportSignalHandler::ProcessEvent);
    QObject::connect(transport, &ITransport::DataReceived, this, &TransportSignalHandler::ProcessData);
}

void TransportSignalHandler::ProcessResponse(Message const &message)
{
    Messages.append(message);
}

void TransportSignalHandler::ProcessData(Message const &message)
{
    Messages.append(message);
}

void TransportSignalHandler::ProcessEvent(Message const &message)
{
    Messages.append(message);
}

}
