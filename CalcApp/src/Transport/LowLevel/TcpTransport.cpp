#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QIODevice>
#include <QObject>
#include <QPair>
#include <QString>
#include <QTcpSocket>

#include <memory>

#include "Common/CommonDefs.h"
#include "Common/Message.h"
#include "Common/TransportConfig.h"
#include "Common/TransportSerialization.h"
#include "TcpTransport.h"

namespace CalcApp
{

namespace
{

void SendData(QTcpSocket *socket, MessagePtr message)
{
    QByteArray buffer;
    QDataStream output(&buffer, QIODevice::WriteOnly);
    output.setVersion(DataStreamVersion);
    TransportSerializer::Serialize(message, output);
    socket->write(buffer);
}

QPair<MessageHeader, QByteArray> StartReadData(QTcpSocket *socket)
{
    if (socket->bytesAvailable() < TransportSerializer::GetMessageHeaderSize())
            return qMakePair(MessageHeader(), QByteArray());
    QDataStream input(socket);
    input.setVersion(DataStreamVersion);
    MessageHeader header = TransportSerializer::DeserializeHeader(input);
    if (socket->bytesAvailable() < header.Size)
        return qMakePair(header, QByteArray());
    return qMakePair(header, TransportSerializer::DeserializeBody(header, input));
}

QByteArray ContinueReadData(QTcpSocket *socket, MessageHeader const &header)
{
    if (socket->bytesAvailable() < header.Size)
        return QByteArray();
    QDataStream input(socket);
    input.setVersion(DataStreamVersion);
    return TransportSerializer::DeserializeBody(header, input);
}

QPair<MessageHeader, QByteArray> ReadData(QTcpSocket *socket, MessageHeader const &header)
{
    return header.Size == 0 ? StartReadData(socket) : qMakePair(header, ContinueReadData(socket, header));
}

}

TcpTransport::TcpTransport(TransportConfig const &transportConfig, QObject *parent) :
    QObject(parent),
    _address(transportConfig.TcpAddress),
    _port(transportConfig.TcpPort),
    _socket(new QTcpSocket(this))
{
    QObject::connect(_socket, &QTcpSocket::readyRead, this, &TcpTransport::ProcessRead);
}

void TcpTransport::Connect()
{
    _socket->connectToHost(QHostAddress(_address), _port);
}

void TcpTransport::Send(MessagePtr message)
{
    SendData(_socket, message);
}

void TcpTransport::ProcessRead()
{
    forever
    {
        QPair<MessageHeader, QByteArray> data = ReadData(_socket, _messageHeader);
        if (data.second.isEmpty())
        {
            _messageHeader = data.first;
            return;
        }
        // TODO (std_string) : use more functional style
        if (data.first.Type == MessageType::EVENT)
            emit EventReceived(std::make_shared<Message>(MessageType::EVENT, data.second));
        else if (data.first.Type == MessageType::RESPONSE)
            emit ResponseReceived(std::make_shared<Message>(MessageType::RESPONSE, data.second));
    }
}

}
