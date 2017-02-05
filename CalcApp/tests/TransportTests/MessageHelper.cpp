#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QtGlobal>

#include <vector>

#include "Message.h"
#include "MessageHelper.h"
#include "MessageInfo.h"
#include "MessageInfoFactory.h"

namespace CalcApp
{

Message CreateMessage(quint8 packageNumber, quint8 calcNumber)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_5);
    char someData[] = {10, 11, 12, 13};
    stream << static_cast<quint32>(packageNumber) << static_cast<quint32>(calcNumber) << someData;
    return Message(MessageType::DATA, data);
}

MessageData CreateMessageData(quint8 packageNumber, quint8 calcNumber)
{
    return MessageData(MessageInfo(packageNumber, calcNumber), CreateMessage(packageNumber, calcNumber));
}

MessageInfo CreateMessageInfo(std::vector<char> const &data)
{
    return CreateMessageInfo(Message(MessageType::DATA, QByteArray(data.data(), data.size())));
}

}
