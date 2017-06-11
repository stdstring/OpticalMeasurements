#include <QObject>
#include <QThread>

#include <memory>

#include "Common/CommonDefs.h"
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
    void Send(MessagePtr message);
    // for interaction with Transport
    void ResponseReceived(MessagePtr message);
    void DataReceived(MessagePtr message);
    void DataProcessFailed();
    void EventReceived(MessagePtr message);

public slots:
    void ProcessStart();
    void ProcessStop();

private slots:
    void ProcessConnect();
    void ProcessSend(MessagePtr message);
};

class TransportService : public ITransport
{
public:
    TransportService(ITransportFactory *transportFactory, TransportConfig const &transportConfig, QObject *parent = nullptr);
    ~TransportService();

    virtual void Connect() override;
    virtual void Send(MessagePtr message) override;

private:
    std::shared_ptr<QThread> _workerThread;
    std::shared_ptr<TransportServiceWorker> _worker;
};

}
