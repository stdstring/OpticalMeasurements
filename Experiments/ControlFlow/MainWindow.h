#pragma once

#include <QAbstractSocket>
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    QTcpServer *_server;
    QTcpSocket *_serverSocket;
    QTcpSocket *_clientSocket;

private slots:
    void SendEventButtonClick();
    void SendRequestButtonClick();
    void ClientConnected();
    void ClientRead();
    void ClientDisconnected();
    void ConnectedToServer();
    void Error(QAbstractSocket::SocketError socketError);
};
