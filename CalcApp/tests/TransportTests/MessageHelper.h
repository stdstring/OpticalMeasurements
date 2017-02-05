#pragma once

#include <QtGlobal>

#include <vector>

#include "Message.h"
#include "MessageInfo.h"

namespace CalcApp
{

Message CreateMessage(quint8 packageNumber, quint8 calcNumber);
MessageData CreateMessageData(quint8 packageNumber, quint8 calcNumber);
MessageInfo CreateMessageInfo(std::vector<char> const &data);

}
