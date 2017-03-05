#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QIODevice>
#include <QObject>
#include <QPair>
#include <QString>
#include <QTcpSocket>

#include "Common/Message.h"
#include "Common/TransportConfig.h"
#include "TcpTransport.h"

namespace CalcApp
{

namespace
{

// TODO (std_string) : move into some common place

// format of all incoming/outgoing messages:
// tag (quint32) - probably added in future
// size (quint32)
// byte array

void SendData(QTcpSocket *socket, Message const &message)
{
    QByteArray buffer;
    QDataStream output(&buffer, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_5);
    // tag (quint32) - probably added in future
    // size (quint32)
    output << static_cast<quint32>(message.GetData().size());
    // byte array
    output << message.GetData();
    socket->write(buffer);
}

QPair<quint32, QByteArray> StartReadData(QTcpSocket *socket)
{
    // tag (quint32) - probably added in future
    // size (quint32)
    if (socket->bytesAvailable() < sizeof(quint32))
        return qMakePair(0, QByteArray());
    QDataStream input(socket);
    quint32 size = 0;
    input >> size;
    if (socket->bytesAvailable() < size)
        return qMakePair(size, QByteArray());
    // byte array
    QByteArray data;
    input >> data;
    return qMakePair(size, data);
}

QByteArray ContinueReadData(QTcpSocket *socket, quint32 size)
{
    if (socket->bytesAvailable() < size)
        return QByteArray();
    // byte array
    QByteArray data;
    QDataStream input(socket);
    input >> data;
    return data;
}

QPair<quint32, QByteArray> ReadData(QTcpSocket *socket, quint32 size)
{
    return size == 0 ? StartReadData(socket) : qMakePair(size, ContinueReadData(socket, size));
}

}

TcpTransport::TcpTransport(TransportConfig const &transportConfig, QObject *parent) :
    QObject(parent),
    _address(transportConfig.TcpAddress),
    _port(transportConfig.TcpPort),
    _socket(new QTcpSocket(this)),
    _messageSize(0),
    _state(TcpTransportState::WAITING_EVENT)
{
    QObject::connect(_socket, &QTcpSocket::readyRead, this, &TcpTransport::ProcessRead);
}

void TcpTransport::Connect()
{
    _socket->connectToHost(QHostAddress(_address), _port);
}

void TcpTransport::Send(Message const &message)
{
    SendData(_socket, message);
    _state = TcpTransportState::WAITING_RESPONSE;
}

void TcpTransport::ProcessRead()
{
    forever
    {
        QPair<quint32, QByteArray> data = ReadData(_socket, _messageSize);
        if (data.second.isEmpty())
        {
            _messageSize = data.first;
            return;
        }
        if (_state == TcpTransportState::WAITING_EVENT)
            emit EventReceived(Message(MessageType::EVENT, data.second));
        if (_state == TcpTransportState::WAITING_RESPONSE)
        {
            emit ResponseReceived(Message(MessageType::RESPONSE, data.second));
            _state = TcpTransportState::WAITING_EVENT;
        }
    }
}

}
