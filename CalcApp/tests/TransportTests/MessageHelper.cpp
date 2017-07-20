#include <QByteArray>
#include <QVector>

#include <memory>

#include "Common/CommonDefs.h"
#include "Common/Message.h"
#include "MessageHelper.h"

namespace CalcApp
{

MessagePtr CreateMessage(MessageType messageType, QVector<char> const &data)
{
    return std::make_shared<Message>(messageType, QByteArray(data.data(), data.size()));
}

MessagePtr CreateDataMessage(int packageNumber, int calcNumber, QVector<char> const &data)
{
    QByteArray dest;
    QDataStream stream(&dest, QIODevice::WriteOnly);
    stream.setVersion(DataStreamVersion);
    stream << static_cast<quint32>(packageNumber) << static_cast<quint32>(calcNumber) << data;
    return std::make_shared<Message>(MessageType::DATA, dest);
}

MessageData CreateMessageData(int packageNumber, int calcNumber, QVector<char> const &data)
{
    return MessageData(MessageInfo(packageNumber, calcNumber), CreateDataMessage(packageNumber, calcNumber, data));
}

}
