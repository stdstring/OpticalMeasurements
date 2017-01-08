#pragma once

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QThread>
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

class ServerTransport : public QObject
{
    Q_OBJECT
public:
    ServerTransport(quint16 tcpPort);
    void SendEvent(QString const &event);
    void SendData(QString const &data);

private:
    quint16 _tcpPort;
    QTcpServer *_server;
    QTcpSocket *_tcpSocket;
    quint16 _tcpMessageSize;
    QUdpSocket *_udpSocket;

signals:
    void RequestReceived(RequestMessage const &message);
    void SendingEvent(QString const &event);
    void SendingData(QString const &data);

public slots:
    void ProcessStart();
    void ProcessFinish();

private slots:
    void TcpClientConnected();
    void ProcessClientRead();
    void TcpClientDisconnected();
    void ProcessSendEvent(QString const &event);
    void ProcessSendData(QString const &data);
};

class ClientTransport : public QObject
{
    Q_OBJECT
public:
    ClientTransport(QString const &host, quint16 tcpPort, quint16 udpPort, QObject *parent);
    void ConnectToServer();
    QString Exchange(QString const &request);

private:
    QString _host;
    quint16 _tcpPort;
    quint16 _udpPort;
    QTcpSocket *_tcpSocket;
    quint16 _tcpMessageSize;
    QUdpSocket *_udpSocket;

signals:
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
    QThread *_serverThread;
    ServerTransport *_serverTransport;
    ClientTransport *_clientTransport;

private slots:
    void SendEventButtonClick();
    void SendRequestButtonClick();
    void ProcessRequest(RequestMessage const &message);
    void ProcessEvent(EventMessage const &message);
    void ProcessData(DataMessage const &message);
};
