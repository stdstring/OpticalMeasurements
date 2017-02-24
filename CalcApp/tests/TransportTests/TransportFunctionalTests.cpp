#include <QList>

#include "gtest/gtest.h"

#include "Message.h"
#include "MessageHelper.h"
#include "TestServer.h"
#include "TransportConfig.h"

namespace CalcApp
{

namespace
{

// TODO (std_string) : think about location of this data
const quint16 TcpPortNumber = 6666;
const quint16 UdpPortNumber = 7777;
const QString ServerAddress = "127.0.0.1";
const int TimerInterval = 400;
const quint32 MaxDelayedCount = 2;

const TestServerConfig serverConfig(TimerInterval, ServerAddress, TcpPortNumber, UdpPortNumber);
const TransportConfig transportConfig(MaxDelayedCount, ServerAddress, TcpPortNumber, UdpPortNumber);

}

TEST(TransportFunctionalTests, Test1)
{
    QList<Message> serverData = {CreateMessage(MessageType::RESPONSE, {11, 12, 13})};
    TestServerRunner server(serverConfig);
    QList<ClientEntry> clientData = {ClientEntry(CreateMessagePtr(MessageType::REQUEST, {66}), CreateMessage(MessageType::RESPONSE, {11, 12, 13}))};
    server.Start(serverData);
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}

}
