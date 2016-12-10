#include <stdexcept>

#include <QTGlobal>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "MainWindow.h"
#include "ui_MainWindow.h"

const quint16 PortNumber = 6666;
const char *HostName = "localhost";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _server(nullptr),
    _serverSocket(nullptr),
    _clientSocket(nullptr)
{
    _ui->setupUi(this);
    QObject::connect(_ui->SendRequestButton, &QPushButton::clicked, this, &MainWindow::SendRequestButtonClick);
    QObject::connect(_ui->SendEventButton, &QPushButton::clicked, this, &MainWindow::SendEventButtonClick);
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
}

MainWindow::~MainWindow()
{
    if (_server != nullptr)
        _server->close();
    delete _ui;
}

void MainWindow::SendEventButtonClick()
{
}

void MainWindow::SendRequestButtonClick()
{
}

void MainWindow::ClientConnected()
{
    _serverSocket = _server->nextPendingConnection();
    QObject::connect(_serverSocket, &QTcpSocket::disconnected, this, &MainWindow::ClientDisconnected);
    QObject::connect(_serverSocket, &QTcpSocket::readyRead, this, &MainWindow::ClientRead);
}

void MainWindow::ClientDisconnected()
{
    delete _serverSocket;
    _serverSocket = nullptr;
}

void MainWindow::ClientRead()
{
}

void MainWindow::ConnectedToServer()
{
}

void MainWindow::Error(QAbstractSocket::SocketError socketError)
{
}
