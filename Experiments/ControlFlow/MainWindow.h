#pragma once

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

namespace Ui {
class MainWindow;
}

struct RequestMessage
{
public:
    RequestMessage() {}
    RequestMessage(QString const &data) : Data(data) {}
    QString Data;
};


struct ResponseMessage
{
public:
    ResponseMessage() {}
    ResponseMessage(QString const &data) : Data(data) {}
    QString Data;
};

struct EventMessage
{
public:
    EventMessage() {}
    EventMessage(QString const &data) : Data(data) {}
    QString Data;
};

struct DataMessage
{
public:
    DataMessage() {}
    DataMessage(QString const &data) : Data(data) {}
    QString Data;
};

enum ClientState { WAIT_EVENTS, WAIT_RESPONSE };

class ServerTransport : public QObject
{
    Q_OBJECT
public:
    ServerTransport(quint16 tcpPort, QObject *parent);
    void SendEvent(QString const &event);
    void SendData(QString const &data);

private:
    QTcpServer *_server;
    QTcpSocket *_tcpSocket;
    quint16 _tcpMessageSize;
    QUdpSocket *_udpSocket;

signals:
    void RequestReceived(RequestMessage const &message);

private slots:
    void TcpClientConnected();
    void ProcessClientRead();
    void TcpClientDisconnected();
};

class ClientTransport : public QObject
{
    Q_OBJECT
public:
    ClientTransport(QString const &host, quint16 tcpPort, quint16 udpPort, QObject *parent);
    void ConnectToServer();
    void ProcessRequest(QString const &request);

private:
    QString _host;
    quint16 _tcpPort;
    quint16 _udpPort;
    QTcpSocket *_tcpSocket;
    quint16 _tcpMessageSize;
    ClientState _state;
    QUdpSocket *_udpSocket;

signals:
    void ResponseReceived(ResponseMessage const &message);
    void EventReceived(EventMessage const &message);
    void DataReceived(DataMessage const &message);

private slots:
    void ProcessTcpRead();
    void ProcessUdpRead();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    ServerTransport *_serverTransport;
    ClientTransport *_clientTransport;

private slots:
    void SendEventButtonClick();
    void SendRequestButtonClick();
    void ProcessRequest(RequestMessage const &message);
    void ProcessResponse(ResponseMessage const &message);
    void ProcessEvent(EventMessage const &message);
    void ProcessData(DataMessage const &message);
};
