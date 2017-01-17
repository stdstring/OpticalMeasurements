#pragma once

#include <QByteArray>

namespace CalcApp
{

enum MessageType { REQUEST, RESPONSE, DATA, EVENT };

class Message
{
public:
    Message(MessageType type, QByteArray const &data) : _type(type), _data(data) {}
    Message(MessageType type, QByteArray &&data) : _type(type), _data(data) {}
    MessageType GetType() const { return _type; }
    QByteArray const& GetData() const { return _data; }

    //Message() = delete;
    //Message(Message const&) = delete;
    //Message(Message&&) = delete;
    //Message& operator=(Message const&) = delete;
    //Message& operator=(Message&&) = delete;

private:
    MessageType _type;
    QByteArray _data;
};

}
