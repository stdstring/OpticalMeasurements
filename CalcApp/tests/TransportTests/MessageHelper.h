#pragma once

#include <QVector>

#include "Common/CommonDefs.h"
#include "Common/Message.h"
#include "MessageInfo.h"

namespace CalcApp
{

MessagePtr CreateMessage(MessageType messageType, QVector<char> const &data);
MessagePtr CreateDataMessage(int packageNumber, quint8 calcNumber, QVector<char> const &data);
MessageData CreateMessageData(int packageNumber, int calcNumber, QVector<char> const &data);

}
