#include <QByteArray>
#include <QDataStream>
#include <QtGlobal>

#include <stdexcept>

#include "Message.h"
#include "TransportSerialization.h"

namespace CalcApp
{

MessageHeader::MessageHeader() : Size(0)
{
}

MessageHeader::MessageHeader(MessageType type, quint32 size) : Type(type), Size(size)
{
}

int TransportSerializer::GetMessageHeaderSize()
{
    // 4 byte for type, 4 byte for size
    return sizeof(quint32) + sizeof(quint32);
}

void TransportSerializer::Serialize(Message const &message, QDataStream &stream)
{
    QByteArray data = message.GetData();
    stream << static_cast<quint32>(message.GetType()) << static_cast<quint32>(data.size());
    stream.writeRawData(data.constData(), data.size());
}

MessageHeader TransportSerializer::DeserializeHeader(QDataStream &stream)
{
    quint32 type;
    quint32 size;
    stream >> type >> size;
    return MessageHeader(static_cast<MessageType>(type), size);
}

QByteArray TransportSerializer::DeserializeBody(MessageHeader const &header, QDataStream &stream)
{
    QByteArray data;
    data.resize(header.Size);
    // TODO (std_string) : use more specific exception
    if (stream.readRawData(data.data(), header.Size) != header.Size)
        throw std::logic_error("wrong data");
    return data;
}

}
