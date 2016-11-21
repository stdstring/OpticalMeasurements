#pragma once

#include <QByteArray>
#include <QtPlugin>

namespace CalcApp
{

enum MessageType { REQUEST, RESPONSE, DATA, EVENT };

class Message
{
public:
    Message() {}
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

class ITransport
{
public:
    // request-response exchange
    virtual Message ProcessControlCmd(Message const &request) = 0;
    // retrieve data/events
    // TODO (std_string) : think about signals/slots for events
    virtual bool HasInput() const = 0;
    virtual Message RetrieveInput() = 0;
    virtual ~ITransport() { /* do nothing */ }
};

}

Q_DECLARE_INTERFACE(CalcApp::ITransport, "com.stdstring.CalcApp.ITransport")
