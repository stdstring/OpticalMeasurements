#pragma once

#include <QByteArray>
#include <QDataStream>
#include <QtGlobal>

#include <tuple>

#include "CommonDefs.h"
#include "Message.h"

namespace CalcApp
{

struct MessageHeader
{
public:
    MessageHeader();
    MessageHeader(MessageType type, quint32 size);

    MessageType Type;
    quint32 Size;
};

class TransportSerializer
{
public:
    static int GetMessageHeaderSize();
    static void Serialize(MessagePtr message, QDataStream &stream);
    static MessageHeader DeserializeHeader(QDataStream &stream);
    static QByteArray DeserializeBody(MessageHeader const &header, QDataStream &stream);
    static std::tuple<MessageHeader, QByteArray> Deserialize(QDataStream &stream);

    TransportSerializer() = delete;
    TransportSerializer(TransportSerializer const&) = delete;
    TransportSerializer(TransportSerializer&&) = delete;
    TransportSerializer& operator=(TransportSerializer const&) = delete;
    TransportSerializer& operator=(TransportSerializer&&) = delete;
};

}
