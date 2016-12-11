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

const quint16 PortNumber = 6666;
const char *HostName = "localhost";

void SendData(QTcpSocket *socket, QString const &data)
{
    QByteArray buffer;
    QDataStream output(&buffer, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_5);
    output << static_cast<quint16>(data.size());
    output << data;
    socket->write(buffer);
}

// TODO (std_string) : not suitable for real world
QString ReadData(QTcpSocket *socket)
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _server(nullptr),
    _serverSocket(nullptr),
    _clientSocket(nullptr),
    _clientState(ClientState::WAIT_EVENTS)
{
    _ui->setupUi(this);
    QObject::connect(_ui->SendRequestButton, &QPushButton::clicked, this, &MainWindow::SendRequestButtonClick);
    QObject::connect(_ui->SendFromServerButton, &QPushButton::clicked, this, &MainWindow::SendEventButtonClick);
    // server listen
    _server = new QTcpServer(this);
    if (!_server->listen(QHostAddress::Any, PortNumber))
    {
        throw std::logic_error("Listen error");
    }
    QObject::connect(_server, &QTcpServer::newConnection, this, &MainWindow::ClientConnected);
    // client connect
    _clientSocket = new QTcpSocket(this);
    _clientSocket->connectToHost(HostName, PortNumber);
    QObject::connect(_clientSocket, &QTcpSocket::readyRead, this, &MainWindow::ReadFromServer);
}

MainWindow::~MainWindow()
{
    if (_server != nullptr)
        _server->close();
    delete _ui;
}

void MainWindow::SendEventButtonClick()
{
    if (_ui->EventInput->text().isEmpty())
        return;
    SendData(_serverSocket, _ui->EventInput->text());
    _ui->EventInput->clear();
}

void MainWindow::SendRequestButtonClick()
{
    if (_ui->RequestInput->text().isEmpty())
        return;
    _clientState = ClientState::WAIT_RESPONSE;
    SendData(_clientSocket, _ui->RequestInput->text());
    _ui->RequestInput->clear();
}

void MainWindow::ClientConnected()
{
    _serverSocket = _server->nextPendingConnection();
    QObject::connect(_serverSocket, &QTcpSocket::disconnected, this, &MainWindow::ClientDisconnected);
    QObject::connect(_serverSocket, &QTcpSocket::readyRead, this, &MainWindow::ReadFromClient);
    SendData(_serverSocket, "Client connected");
}

void MainWindow::ClientDisconnected()
{
    //delete _serverSocket;
    _serverSocket = nullptr;
}

void MainWindow::ReadFromClient()
{
    QString data = ReadData(_serverSocket);
    _ui->RequestsList->addItem(QString::asprintf("REQUEST : %s", data.toStdString().c_str()));
    SendData(_serverSocket, QString::asprintf("%s is readed", data.toStdString().c_str()));
}

void MainWindow::ReadFromServer()
{
    QString data = ReadData(_clientSocket);
    const char *description = _clientState == ClientState::WAIT_EVENTS ? "EVENT" : "RESPONSE";
    _ui->ResponsesAndEventsList->addItem(QString::asprintf("%s : %s", description, data.toStdString().c_str()));
    _clientState = ClientState::WAIT_EVENTS;
}
