#include <QByteArray>
#include <QDataStream>
#include <QList>
#include <QObject>
#include <QUdpSocket>

#include "Common/Message.h"
#include "UdpTransport.h"

namespace CalcApp
{

namespace
{

// format of all incoming/outgoing messages:
// tag (quint32) - probably added in future
// size (quint32)
// byte array

QByteArray ReadSingleData(QUdpSocket *socket)
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(buffer.data(), buffer.size());
    QDataStream input(&buffer, QIODevice::ReadOnly);
    // tag (quint32) - probably added in future
    // size (quint32)
    quint32 size = 0;
    input >> size;
    // byte array
    QByteArray data;
    input >> data;
    return data;
}

QList<QByteArray> ReadData(QUdpSocket *socket)
{
    QList<QByteArray> dest;
    while (socket->hasPendingDatagrams())
    {
        QByteArray data = ReadSingleData(socket);
        dest.append(data);
    }
    return dest;
}

}

UdpTransport::UdpTransport(quint16 port, QObject *parent) :
    QObject(parent),
    _port(port),
    _socket(new QUdpSocket(this))
{
    QObject::connect(_socket, &QUdpSocket::readyRead, this, &UdpTransport::ProcessRead);
}

void UdpTransport::Connect()
{
    _socket->bind(_port);
}

void UdpTransport::ProcessRead()
{
    QList<QByteArray> result = ReadData(_socket);
    foreach(QByteArray data, result)
    {
        emit DataReceived(Message(MessageType::DATA, data));
    }
}

}
