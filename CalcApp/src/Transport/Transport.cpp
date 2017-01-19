#include <QObject>

#include "ITransport.h"
#include "Message.h"
#include "Transport.h"

namespace CalcApp
{

Transport::Transport(ITransport *transportLowLevel, QObject *parent) : ITransport(parent)
{
}

void Transport::Connect()
{
}

void Transport::Send(Message const &message)
{
}

}
