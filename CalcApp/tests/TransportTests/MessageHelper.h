#pragma once

#include <QtGlobal>
#include <QVector>

#include "Message.h"
#include "MessageInfo.h"

namespace CalcApp
{

Message CreateMessage(MessageType messageType, QVector<char> const &data = {});
Message CreateMessage(quint8 packageNumber, quint8 calcNumber, QVector<char> const &data = {});
MessageData CreateMessageData(quint8 packageNumber, quint8 calcNumber, QVector<char> const &data = {});
MessageInfo CreateMessageInfo(QVector<char> const &data);

}
