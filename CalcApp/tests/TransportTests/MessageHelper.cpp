#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QtGlobal>
#include <QVector>

#include <memory>

#include "Message.h"
#include "MessageHelper.h"
#include "MessageInfo.h"
#include "MessageInfoFactory.h"

namespace CalcApp
{

Message CreateMessage(MessageType messageType, QVector<char> const &data)
{
    return Message(messageType, QByteArray(data.data(), data.size()));
}

std::shared_ptr<Message> CreateMessagePtr(MessageType messageType, QVector<char> const &data)
{
    return std::shared_ptr<Message>(new Message(messageType, QByteArray(data.data(), data.size())));
}

Message CreateDataMessage(quint8 packageNumber, quint8 calcNumber, QVector<char> const &data)
{
    QByteArray dest;
    QDataStream stream(&dest, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_5);
    stream << static_cast<quint32>(packageNumber) << static_cast<quint32>(calcNumber) << data;
    return Message(MessageType::DATA, dest);
}

MessageData CreateMessageData(quint8 packageNumber, quint8 calcNumber, QVector<char> const &data)
{
    return MessageData(MessageInfo(packageNumber, calcNumber), CreateDataMessage(packageNumber, calcNumber, data));
}

MessageInfo CreateMessageInfo(QVector<char> const &data)
{
    return CreateMessageInfo(Message(MessageType::DATA, QByteArray(data.data(), data.size())));
}

}
