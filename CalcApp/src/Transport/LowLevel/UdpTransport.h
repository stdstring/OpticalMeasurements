#pragma once

#include <QObject>
#include <QUdpSocket>

#include "Common/CommonDefs.h"
#include "Common/TransportConfig.h"

#if defined(TRANSPORT_LIBRARY)
#define TRANSPORT_LIBRARY_DLLSPEC Q_DECL_EXPORT
#else
#define TRANSPORT_LIBRARY_DLLSPEC Q_DECL_IMPORT
#endif

namespace CalcApp
{

class TRANSPORT_LIBRARY_DLLSPEC UdpTransport : public QObject
{
    Q_OBJECT
public:
    UdpTransport(TransportConfig const &transportConfig, QObject *parent);
    void Connect();
    void Disconnect();

signals:
    void DataReceived(MessagePtr message);

private:
    quint16 _port;
    QUdpSocket *_socket;

private slots:
    void ProcessRead();
};

}
