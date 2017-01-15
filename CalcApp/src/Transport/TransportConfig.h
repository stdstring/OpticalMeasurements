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

    TransportConfig(QString const &tcpAddress, quint16 tcpPort, quint16 udpPort) :
        TcpAddress(tcpAddress),
        TcpPort(tcpPort),
        UdpPort(udpPort)
    {
    }

    QString TcpAddress;
    quint16 TcpPort;
    quint16 UdpPort;
};

}
