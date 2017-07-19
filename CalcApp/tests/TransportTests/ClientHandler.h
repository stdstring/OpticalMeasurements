#pragma once

#include <QList>
#include <QObject>
#include <QThread>

#include <memory>

#include "Common/ITransport.h"
#include "Common/Message.h"
#include "Common/TransportConfig.h"

namespace CalcApp
{

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    static void Check(TransportConfig const &config, QList<MessagePtr> const &messages);

private:
    ClientHandler(TransportConfig const &config, QThread *initThread, QList<MessagePtr> const &messages);

    TransportConfig _config;
    std::shared_ptr<ITransport> _transport;
    QThread *_initThread;
    QList<MessagePtr> _messages;

private slots:
    void ProcessStart();
    void ProcessFinish();
    void ProcessMessage(MessagePtr message);
};

}
