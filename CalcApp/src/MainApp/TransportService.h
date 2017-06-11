#include <QObject>
#include <QThread>

#include <memory>

#include "Common/ITransport.h"
#include "Common/ITransportFactory.h"
#include "Common/TransportConfig.h"

namespace CalcApp
{

class TransportServiceWorker : public QObject
{
    Q_OBJECT
public:
    TransportServiceWorker(ITransportFactory *transportFactory, TransportConfig const &transportConfig);

private:
    ITransportFactory *_transportFactory;
    TransportConfig const &_transportConfig;
    std::shared_ptr<ITransport> _transport;

signals:
    // for interaction with TransportService
    void Connect();
    void Send(Message /*const &*/message);
    // for interaction with Transport
    void ResponseReceived(Message /*const &*/message);
    void DataReceived(Message /*const &*/message);
    void DataProcessFailed();
    void EventReceived(Message /*const &*/message);

public slots:
    void ProcessStart();
    void ProcessStop();

private slots:
    void ProcessConnect();
    void ProcessSend(Message /*const &*/message);
};

class TransportService : public ITransport
{
public:
    TransportService(ITransportFactory *transportFactory, TransportConfig const &transportConfig, QObject *parent = nullptr);
    ~TransportService();

    virtual void Connect() override;
    virtual void Send(Message /*const &*/message) override;

private:
    std::shared_ptr<QThread> _workerThread;
    std::shared_ptr<TransportServiceWorker> _worker;
};

}
