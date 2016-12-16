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

void ProcessTcpDataFromClient(QString const &data, QListWidget *destList, QTcpSocket *socket)
{
    QString item;
    QTextStream(&item) << "REQUEST : " << data;
    destList->addItem(item);
    QString response;
    QTextStream(&response) << data << " is readed";
    SendTcpData(socket, response);
}

void ProcessTcpDataFromServer(QString const &data, QListWidget *destList, ClientState &state)
{
    QString item;
    QTextStream(&item) << (state == ClientState::WAIT_EVENTS ? "EVENT" : "RESPONSE") << " : " << data;
    destList->addItem(item);
    state = ClientState::WAIT_EVENTS;
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _server(nullptr),
    _serverTcpSocket(nullptr),
    _serverMessageSize(0),
    _clientTcpSocket(nullptr),
    _clientMessageSize(0),
    _clientState(ClientState::WAIT_EVENTS),
    _serverUdpSocket(nullptr),
    _clientUdpSocket(nullptr)
{
    _ui->setupUi(this);
    QObject::connect(_ui->SendRequestButton, &QPushButton::clicked, this, &MainWindow::SendRequestButtonClick);
    QObject::connect(_ui->SendFromServerButton, &QPushButton::clicked, this, &MainWindow::SendEventButtonClick);
    // server listen
    _server = new QTcpServer(this);
    if (!_server->listen(QHostAddress::Any, TcpPortNumber))
    {
        throw std::logic_error("Listen error");
    }
    QObject::connect(_server, &QTcpServer::newConnection, this, &MainWindow::TcpClientConnected);
    // client connect
    _clientTcpSocket = new QTcpSocket(this);
    _clientTcpSocket->connectToHost(HostName, TcpPortNumber);
    QObject::connect(_clientTcpSocket, &QTcpSocket::readyRead, this, &MainWindow::ReadFromTcpServer);
    // server data
    _serverUdpSocket = new QUdpSocket(this);
    // client data
    _clientUdpSocket = new QUdpSocket(this);
    _clientUdpSocket->bind(UdpPortNumber);
    QObject::connect(_clientUdpSocket, &QUdpSocket::readyRead, this, &MainWindow::ReadFromUdpServer);
}

MainWindow::~MainWindow()
{
    if (_server != nullptr)
        _server->close();
    delete _ui;
}

void MainWindow::SendEventButtonClick()
{
    if (!_ui->EventInput->text().isEmpty())
        SendTcpData(_serverTcpSocket, _ui->EventInput->text());
    if (!_ui->DataInput->text().isEmpty())
        SendUdpData(_serverUdpSocket, _ui->DataInput->text());
    _ui->EventInput->clear();
    _ui->DataInput->clear();
}

void MainWindow::SendRequestButtonClick()
{
    if (_ui->RequestInput->text().isEmpty())
        return;
    _clientState = ClientState::WAIT_RESPONSE;
    SendTcpData(_clientTcpSocket, _ui->RequestInput->text());
    _ui->RequestInput->clear();
}

void MainWindow::TcpClientConnected()
{
    _serverTcpSocket = _server->nextPendingConnection();
    QObject::connect(_serverTcpSocket, &QTcpSocket::disconnected, this, &MainWindow::TcpClientDisconnected);
    QObject::connect(_serverTcpSocket, &QTcpSocket::readyRead, this, &MainWindow::ReadFromTcpClient);
    SendTcpData(_serverTcpSocket, "Client connected");
}

void MainWindow::TcpClientDisconnected()
{
    //delete _serverSocket;
    _serverTcpSocket = nullptr;
}

void MainWindow::ReadFromTcpClient()
{
    for(;;)
    {
        QPair<quint16, QString> data = ReadTcpData(_serverTcpSocket, _serverMessageSize);
        if (data.second.isEmpty())
        {
            _serverMessageSize = data.first;
            return;
        }
        ProcessTcpDataFromClient(data.second, _ui->RequestsList, _serverTcpSocket);
    }
}

void MainWindow::ReadFromTcpServer()
{
    for(;;)
    {
        QPair<quint16, QString> data = ReadTcpData(_clientTcpSocket, _clientMessageSize);
        if (data.second.isEmpty())
        {
            _clientMessageSize = data.first;
            return;
        }
        ProcessTcpDataFromServer(data.second, _ui->ResponsesEventsDataList, _clientState);
    }
}

void MainWindow::ReadFromUdpServer()
{
    QList<QString> result = ReadUdpData(_clientUdpSocket);
    foreach(QString data, result)
    {
        QString item;
        QTextStream(&item) << "DATA : " << data;
        _ui->ResponsesEventsDataList->addItem(item);
    }
}
