#include "Common/ITransport.h"
#include "Common/ITransportFactory.h"
#include "Common/TransportConfig.h"
#include "TransportService.h"

namespace CalcApp
{

TransportServiceWorker::TransportServiceWorker(ITransportFactory *transportFactory, TransportConfig const &transportConfig) :
    _transportFactory(transportFactory),
    _transportConfig(transportConfig)
{
    QObject::connect(this, &TransportServiceWorker::Connect, this, &TransportServiceWorker::ProcessConnect);
    QObject::connect(this, &TransportServiceWorker::Send, this, &TransportServiceWorker::ProcessSend);
}

void TransportServiceWorker::ProcessStart()
{
    _transport.reset(_transportFactory->Create(_transportConfig, this));
    QObject::connect(_transport.get(), &ITransport::ResponseReceived, this, &TransportServiceWorker::ResponseReceived);
    QObject::connect(_transport.get(), &ITransport::DataReceived, this, &TransportServiceWorker::DataReceived);
    QObject::connect(_transport.get(), &ITransport::DataProcessFailed, this, &TransportServiceWorker::DataProcessFailed);
    QObject::connect(_transport.get(), &ITransport::EventReceived, this, &TransportServiceWorker::EventReceived);
}

void TransportServiceWorker::ProcessStop()
{
    QObject::disconnect(_transport.get(), &ITransport::ResponseReceived, this, &TransportServiceWorker::ResponseReceived);
    QObject::disconnect(_transport.get(), &ITransport::DataReceived, this, &TransportServiceWorker::DataReceived);
    QObject::disconnect(_transport.get(), &ITransport::DataProcessFailed, this, &TransportServiceWorker::DataProcessFailed);
    QObject::disconnect(_transport.get(), &ITransport::EventReceived, this, &TransportServiceWorker::EventReceived);
    _transport.reset();
}

void TransportServiceWorker::ProcessConnect()
{
    _transport.get()->Connect();
}

void TransportServiceWorker::ProcessSend(Message /*const &*/message)
{
    _transport.get()->Send(message);
}

TransportService::TransportService(ITransportFactory *transportFactory, TransportConfig const &transportConfig, QObject *parent) :
    ITransport(parent),
    _workerThread(new QThread()),
    _worker(new TransportServiceWorker(transportFactory, transportConfig))
{
    QObject::connect(_workerThread.get(), &QThread::started, _worker.get(), &TransportServiceWorker::ProcessStart);
    QObject::connect(_workerThread.get(), &QThread::finished, _worker.get(), &TransportServiceWorker::ProcessStop);
    _worker.get()->moveToThread(_workerThread.get());
    _workerThread.get()->start();
}

TransportService::~TransportService()
{
    _workerThread.get()->exit();
    _workerThread.get()->wait();
}

void TransportService::Connect()
{
    emit _worker.get()->Connect();
}

void TransportService::Send(Message /*const &*/message)
{
    emit _worker.get()->Send(message);
}

}
