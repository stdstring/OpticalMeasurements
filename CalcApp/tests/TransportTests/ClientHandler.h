#pragma once

#include <QList>
#include <QObject>
#include <QThread>

#include "Common/ITransport.h"
#include "Common/Message.h"
#include "Common/TransportConfig.h"
#include "ClientEntry.h"

namespace CalcApp
{

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    static void Check(TransportConfig const &config, QList<ClientEntry> const &entries);

private:
    ClientHandler(TransportConfig const &config, QThread *initThread, QList<ClientEntry> const &entries);

    TransportConfig _config;
    ITransport *_transport;
    QThread *_initThread;
    QList<ClientEntry> _entries;

private slots:
    void ProcessStart();
    void ProcessFinish();
    void ProcessMessage(Message const &message);
};

}
