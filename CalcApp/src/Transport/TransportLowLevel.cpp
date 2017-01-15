#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QList>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QUdpSocket>

#include "Message.h"
#include "MessageType.h"
#include "TransportLowLevel.h"

namespace CalcApp
{

namespace
{

// format of all incoming/outgoing messages:
// tag (quint32) - probably added in future
// size (quint32)
// byte array

void SendTcpData(QTcpSocket *socket, Message const &message)
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

QByteArray ReadSingleUdpData(QUdpSocket *socket)
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

QList<QByteArray> ReadUdpData(QUdpSocket *socket)
{
    QList<QByteArray> dest;
    while (socket->hasPendingDatagrams())
    {
        QByteArray data = ReadSingleUdpData(socket);
        dest.append(data);
    }
    return dest;
}

QPair<quint32, QByteArray> StartReadTcpData(QTcpSocket *socket)
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

QByteArray ContinueReadTcpData(QTcpSocket *socket, quint32 size)
{
    if (socket->bytesAvailable() < size)
        return QByteArray();
    // byte array
    QByteArray data;
    QDataStream input(socket);
    input >> data;
    return data;
}

QPair<quint32, QByteArray> ReadTcpData(QTcpSocket *socket, quint32 size)
{
    return size == 0 ? StartReadTcpData(socket) : qMakePair(size, ContinueReadTcpData(socket, size));
}

}

TransportConfig::TransportConfig(QString const &tcpAddress, quint16 tcpPort, quint16 udpPort) :
    TcpAddress(tcpAddress),
    TcpPort(tcpPort),
    UdpPort(udpPort)
{
}

TcpTransport::TcpTransport(QString const &address, quint16 port, QObject *parent) :
    QObject(parent),
    _address(address),
    _port(port),
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
    SendTcpData(_socket, message);
    _state = TcpTransportState::WAITING_RESPONSE;
}

void TcpTransport::ProcessRead()
{
    forever
    {
        QPair<quint32, QByteArray> data = ReadTcpData(_socket, _messageSize);
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
    QList<QByteArray> result = ReadUdpData(_socket);
    foreach(QByteArray data, result)
    {
        emit DataReceived(Message(MessageType::DATA, data));
    }
}


TransportLowLevel::TransportLowLevel(TransportConfig const &config, QObject *parent) :
    TransportLowLevelBase(parent),
    _tcpTransport(new TcpTransport(config.TcpAddress, config.TcpPort, this)),
    _udpTransport(new UdpTransport(config.UdpPort, this))
{
    QObject::connect(_tcpTransport, &TcpTransport::ResponseReceived, this, &TransportLowLevel::ResponseReceived);
    QObject::connect(_tcpTransport, &TcpTransport::EventReceived, this, &TransportLowLevel::EventReceived);
    QObject::connect(_udpTransport, &UdpTransport::DataReceived, this, &TransportLowLevel::DataReceived);
}

void TransportLowLevel::Connect()
{
    _tcpTransport->Connect();
    _udpTransport->Connect();
}

void TransportLowLevel::Send(Message const &message)
{
    _tcpTransport->Send(message);
}

}
