#include <QList>
#include <QObject>

#include "Common/ITransport.h"
#include "Common/Message.h"
#include "TransportSignalHandler.h"

namespace CalcApp
{

TransportSignalHandler::TransportSignalHandler(ITransport *transport, QObject *parent) :
    QObject(parent)
{
    // TODO (std_string) : think about using new syntax
    //QObject::connect(transport, &ITransport::ResponseReceived, this, &TransportSignalHandler::ProcessResponse);
    //QObject::connect(transport, &ITransport::EventReceived, this, &TransportSignalHandler::ProcessEvent);
    //QObject::connect(transport, &ITransport::DataReceived, this, &TransportSignalHandler::ProcessData);
    QObject::connect(transport, SIGNAL(ResponseReceived(Message const&)), this, SLOT(ProcessResponse(Message const&)));
    QObject::connect(transport, SIGNAL(EventReceived(Message const&)), this, SLOT(ProcessEvent(Message const&)));
    QObject::connect(transport, SIGNAL(DataReceived(Message const&)), this, SLOT(ProcessData(Message const&)));
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
