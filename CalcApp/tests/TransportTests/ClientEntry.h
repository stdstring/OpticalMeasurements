#pragma once

#include <memory>

#include "Common/Message.h"

namespace CalcApp
{

struct ClientEntry
{
public:
    ClientEntry(Message const &incomingMessage) :
        ClientEntry(std::shared_ptr<Message>(), incomingMessage)
    {
    }

    ClientEntry(std::shared_ptr<Message> outgoingMessage, Message const &incomingMessage) :
        OutgoingMessage(outgoingMessage),
        IncomingMessage(incomingMessage)
    {
    }

    std::shared_ptr<Message> OutgoingMessage;
    Message IncomingMessage;
};

}
