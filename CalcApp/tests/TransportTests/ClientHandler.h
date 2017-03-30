#pragma once

#include <QList>
#include <QObject>
#include <QThread>

#include "Common/ITransport.h"
#include "Common/Message.h"
#include "Common/TransportConfig.h"

namespace CalcApp
{

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    static void Check(TransportConfig const &config, QList<Message> const &messages);

private:
    ClientHandler(TransportConfig const &config, QThread *initThread, QList<Message> const &messages);

    TransportConfig _config;
    ITransport *_transport;
    QThread *_initThread;
    QList<Message> _messages;

private slots:
    void ProcessStart();
    void ProcessFinish();
    void ProcessMessage(Message const &message);
};

}
