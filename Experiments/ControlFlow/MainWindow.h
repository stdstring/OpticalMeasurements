#pragma once

#include <QAbstractSocket>
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

namespace Ui {
class MainWindow;
}

enum ClientState { WAIT_EVENTS, WAIT_RESPONSE };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    QTcpServer *_server;
    QTcpSocket *_serverTcpSocket;
    quint16 _serverMessageSize;
    QTcpSocket *_clientTcpSocket;
    quint16 _clientMessageSize;
    ClientState _clientState;
    QUdpSocket *_serverUdpSocket;
    QUdpSocket *_clientUdpSocket;

private slots:
    void SendEventButtonClick();
    void SendRequestButtonClick();
    void TcpClientConnected();
    void ReadFromTcpClient();
    void TcpClientDisconnected();
    void ReadFromTcpServer();
    void ReadFromUdpServer();
};
