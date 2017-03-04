#pragma once

#include <QString>

namespace CalcApp
{

struct TransportConfig
{
public:
    TransportConfig()
    {
    }

    TransportConfig(quint32 maxDelayedCount, QString const &tcpAddress, quint16 tcpPort, quint16 udpPort) :
        MaxDelayedCount(maxDelayedCount),
        TcpAddress(tcpAddress),
        TcpPort(tcpPort),
        UdpPort(udpPort)
    {
    }

    quint32 MaxDelayedCount;
    QString TcpAddress;
    quint16 TcpPort;
    quint16 UdpPort;
};

}
