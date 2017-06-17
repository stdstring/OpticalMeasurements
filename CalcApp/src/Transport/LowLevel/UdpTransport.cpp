#include <QByteArray>
#include <QDataStream>
#include <QList>
#include <QObject>
#include <QUdpSocket>

#include <memory>

#include "Common/CommonDefs.h"
#include "Common/Message.h"
#include "Common/TransportConfig.h"
#include "Common/TransportSerialization.h"
#include "UdpTransport.h"

namespace CalcApp
{

namespace
{

QByteArray ReadSingleData(QUdpSocket *socket)
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(buffer.data(), buffer.size());
    QDataStream input(&buffer, QIODevice::ReadOnly);
    input.setVersion(DataStreamVersion);
    MessageHeader header = TransportSerializer::DeserializeHeader(input);
    return TransportSerializer::DeserializeBody(header, input);
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

UdpTransport::UdpTransport(TransportConfig const &transportConfig, QObject *parent) :
    QObject(parent),
    _port(transportConfig.UdpPort),
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
        emit DataReceived(std::make_shared<Message>(MessageType::DATA, data));
    }
}

}
