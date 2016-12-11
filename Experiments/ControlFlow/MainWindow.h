#pragma once

#include <QAbstractSocket>
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

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
    QTcpSocket *_serverSocket;
    QTcpSocket *_clientSocket;
    ClientState _clientState;

private slots:
    void SendEventButtonClick();
    void SendRequestButtonClick();
    void ClientConnected();
    void ReadFromClient();
    void ClientDisconnected();
    void ReadFromServer();
};
