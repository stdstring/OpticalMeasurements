#include <QList>
#include <QObject>

#include "Common/CommonDefs.h"
#include "Common/ITransport.h"
#include "Common/Message.h"
#include "TransportSignalHandler.h"

namespace CalcApp
{

TransportSignalHandler::TransportSignalHandler(ITransport *transport, QObject *parent) :
    QObject(parent),
    DataProcessFailed(false)
{
    QObject::connect(transport, &ITransport::ResponseReceived, this, [this](MessagePtr message){ Messages.append(message); });
    QObject::connect(transport, &ITransport::EventReceived, this, [this](MessagePtr message){ Messages.append(message); });
    QObject::connect(transport, &ITransport::DataReceived, this, [this](MessagePtr message){ Messages.append(message); });
    QObject::connect(transport, &ITransport::DataProcessFailed, this, [this](){ DataProcessFailed = true; });
}

}
