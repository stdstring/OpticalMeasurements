#include <stdexcept>

#include <QTGlobal>
#include <QAbstractSocket>
#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QIODevice>
#include <QList>
#include <QMessageBox>
#include <QObject>
#include <QPair>
#include <QString>
#include <QTextStream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

#include "MainWindow.h"
#include "ui_MainWindow.h"

const quint16 TcpPortNumber = 6666;
const quint16 UdpPortNumber = 7777;
const char *HostName = "localhost";

void SendTcpData(QTcpSocket *socket, QString const &data)
{
    QByteArray buffer;
    QDataStream output(&buffer, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_5);
    output << static_cast<quint16>(data.size());
    output << data;
    socket->write(buffer);
}

QPair<quint16, QString> StartReadTcpData(QTcpSocket *socket)
{
    if (socket->bytesAvailable() < sizeof(quint16))
        return qMakePair(0, QString());
    QDataStream input(socket);
    quint16 size = 0;
    input >> size;
    if (socket->bytesAvailable() < size)
        return qMakePair(size, QString());
    QString data;
    input >> data;
    return qMakePair(size, data);
}

QString ContinueReadTcpData(QTcpSocket *socket, quint16 size)
{
    if (socket->bytesAvailable() < size)
        return QString();
    QString data;
    QDataStream input(socket);
    input >> data;
    return data;
}

QPair<quint16, QString> ReadTcpData(QTcpSocket *socket, quint16 size)
{
    return size == 0 ? StartReadTcpData(socket) : qMakePair(size, ContinueReadTcpData(socket, size));
}

void ProcessNotification(QString const &data, QString const &prefix, QListWidget *destList)
{
    QString item;
    QTextStream(&item) << prefix << " : " << data;
    destList->addItem(item);

}

void SendUdpData(QUdpSocket *socket, QString const &data)
{
    QByteArray buffer;
    QDataStream output(&buffer, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_5);
    output << static_cast<quint16>(data.size());
    output << data;
    socket->writeDatagram(buffer, QHostAddress::LocalHost, UdpPortNumber);
}

QString ReadSingleUdpData(QUdpSocket *socket)
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(buffer.data(), buffer.size());
    QDataStream input(&buffer, QIODevice::ReadOnly);
    quint16 size = 0;
    input >> size;
    QString data;
    input >> data;
    return data;
}

QList<QString> ReadUdpData(QUdpSocket *socket)
{
    QList<QString> dest;
    while (socket->hasPendingDatagrams())
    {
        QString data = ReadSingleUdpData(socket);
        dest.append(data);
    }
    return dest;
}

ServerTransport::ServerTransport(quint16 tcpPort, QObject *parent) :
    QObject(parent),
    _server(new QTcpServer(this)),
    _tcpSocket(nullptr),
    _tcpMessageSize(0),
    _udpSocket(new QUdpSocket(this))
{
    if (!_server->listen(QHostAddress::Any, tcpPort))
    {
        throw std::logic_error("Listen error");
    }
    QObject::connect(_server, &QTcpServer::newConnection, this, &ServerTransport::TcpClientConnected);
}

void ServerTransport::SendEvent(QString const &event)
{
    SendTcpData(_tcpSocket, event);
}

void ServerTransport::SendData(QString const &data)
{
    SendUdpData(_udpSocket, data);
}

void ServerTransport::TcpClientConnected()
{
    _tcpSocket = _server->nextPendingConnection();
    QObject::connect(_tcpSocket, &QTcpSocket::disconnected, this, &ServerTransport::TcpClientDisconnected);
    QObject::connect(_tcpSocket, &QTcpSocket::readyRead, this, &ServerTransport::ProcessClientRead);
    SendTcpData(_tcpSocket, "Client connected");
}

void ServerTransport::ProcessClientRead()
{
    for(;;)
    {
        QPair<quint16, QString> data = ReadTcpData(_tcpSocket, _tcpMessageSize);
        if (data.second.isEmpty())
        {
            _tcpMessageSize = data.first;
            return;
        }
        emit RequestReceived(RequestMessage(data.second));
        QString response;
        QTextStream(&response) << data.second << " is readed";
        SendTcpData(_tcpSocket, response);
    }
}

void ServerTransport::TcpClientDisconnected()
{
    _tcpSocket = nullptr;
}

ClientTransport::ClientTransport(QString const &host, quint16 tcpPort, quint16 udpPort, QObject *parent) :
    QObject(parent),
    _host(host),
    _tcpPort(tcpPort),
    _udpPort(udpPort),
    _tcpSocket(new QTcpSocket(this)),
    _tcpMessageSize(0),
    _state(ClientState::WAIT_EVENTS),
    _udpSocket(new QUdpSocket(this))
{
    QObject::connect(_tcpSocket, &QTcpSocket::readyRead, this, &ClientTransport::ProcessTcpRead);
    QObject::connect(_udpSocket, &QUdpSocket::readyRead, this, &ClientTransport::ProcessUdpRead);
}

void ClientTransport::ConnectToServer()
{
    _tcpSocket->connectToHost(_host, _tcpPort);
    _udpSocket->bind(UdpPortNumber);
}

void ClientTransport::ProcessRequest(QString const &request)
{
    _state = ClientState::WAIT_RESPONSE;
    SendTcpData(_tcpSocket, request);
}

void ClientTransport::ProcessTcpRead()
{
    for(;;)
    {
        QPair<quint16, QString> data = ReadTcpData(_tcpSocket, _tcpMessageSize);
        if (data.second.isEmpty())
        {
            _tcpMessageSize = data.first;
            return;
        }
        if (_state == ClientState::WAIT_RESPONSE)
            emit ResponseReceived(ResponseMessage(data.second));
        if (_state == ClientState::WAIT_EVENTS)
            emit EventReceived(EventMessage(data.second));
        _state = ClientState::WAIT_EVENTS;
    }
}

void ClientTransport::ProcessUdpRead()
{
    QList<QString> result = ReadUdpData(_udpSocket);
    foreach(QString data, result)
    {
        emit DataReceived(DataMessage(data));
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _serverTransport(new ServerTransport(TcpPortNumber, this)),
    _clientTransport(new ClientTransport(HostName, TcpPortNumber, UdpPortNumber, this))
{
    _ui->setupUi(this);
    QObject::connect(_ui->SendRequestButton, &QPushButton::clicked, this, &MainWindow::SendRequestButtonClick);
    QObject::connect(_ui->SendFromServerButton, &QPushButton::clicked, this, &MainWindow::SendEventButtonClick);
    QObject::connect(_serverTransport, &ServerTransport::RequestReceived, this, &MainWindow::ProcessRequest);
    QObject::connect(_clientTransport, &ClientTransport::ResponseReceived, this, &MainWindow::ProcessResponse);
    QObject::connect(_clientTransport, &ClientTransport::EventReceived, this, &MainWindow::ProcessEvent);
    QObject::connect(_clientTransport, &ClientTransport::DataReceived, this, &MainWindow::ProcessData);
    _clientTransport->ConnectToServer();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::SendEventButtonClick()
{
    if (!_ui->EventInput->text().isEmpty())
        _serverTransport->SendEvent(_ui->EventInput->text());
    if (!_ui->DataInput->text().isEmpty())
        _serverTransport->SendData(_ui->DataInput->text());
    _ui->EventInput->clear();
    _ui->DataInput->clear();
}

void MainWindow::SendRequestButtonClick()
{
    if (_ui->RequestInput->text().isEmpty())
        return;
    _clientTransport->ProcessRequest(_ui->RequestInput->text());
    _ui->RequestInput->clear();
}


void MainWindow::ProcessRequest(RequestMessage const &message)
{
    ProcessNotification(message.Data, "REQUEST", _ui->RequestsList);
}

void MainWindow::ProcessResponse(ResponseMessage const &message)
{
    ProcessNotification(message.Data, "RESPONSE", _ui->ResponsesEventsDataList);
}

void MainWindow::ProcessEvent(EventMessage const &message)
{
    ProcessNotification(message.Data, "EVENT", _ui->ResponsesEventsDataList);
}

void MainWindow::ProcessData(DataMessage const &message)
{
    ProcessNotification(message.Data, "DATA", _ui->ResponsesEventsDataList);
}
