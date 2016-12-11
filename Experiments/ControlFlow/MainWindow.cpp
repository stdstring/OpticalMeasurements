#include <stdexcept>

#include <QTGlobal>
#include <QAbstractSocket>
#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QIODevice>
#include <QMessageBox>
#include <QObject>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>

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

// TODO (std_string) : not suitable for real world
QString ReadTcpData(QTcpSocket *socket)
{
    QDataStream input(socket);
    quint16 size = 0;
    input >> size;
    if (socket->bytesAvailable() < size)
        throw std::logic_error("Not all data available");
    QString data;
    input >> data;
    return data;
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

// TODO (std_string) : not suitable for real world
QString ReadUdpData(QUdpSocket *socket)
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _server(nullptr),
    _serverTcpSocket(nullptr),
    _clientTcpSocket(nullptr),
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
    QString data = ReadTcpData(_serverTcpSocket);
    _ui->RequestsList->addItem(QString::asprintf("REQUEST : %s", data.toStdString().c_str()));
    SendTcpData(_serverTcpSocket, QString::asprintf("%s is readed", data.toStdString().c_str()));
}

void MainWindow::ReadFromTcpServer()
{
    QString data = ReadTcpData(_clientTcpSocket);
    const char *description = _clientState == ClientState::WAIT_EVENTS ? "EVENT" : "RESPONSE";
    _ui->ResponsesAndEventsList->addItem(QString::asprintf("%s : %s", description, data.toStdString().c_str()));
    _clientState = ClientState::WAIT_EVENTS;
}

void MainWindow::ReadFromUdpServer()
{
    QString data = ReadUdpData(_clientUdpSocket);
    _ui->ResponsesAndEventsList->addItem(QString::asprintf("DATA : %s", data.toStdString().c_str()));
}
