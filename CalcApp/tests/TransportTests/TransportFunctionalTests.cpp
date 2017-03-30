#include <QList>
#include <QVector>

#include "gtest/gtest.h"

#include "Common/Message.h"
#include "Common/TransportConfig.h"
#include "TestServerCore/TestServerRunner.h"
#include "TestServerCore/TestServerConfig.h"
#include "ClientEntry.h"
#include "ClientHandler.h"
#include "MessageHelper.h"

namespace CalcApp
{

namespace
{

// TODO (std_string) : think about location of this data
const quint16 TcpPortNumber = 6666;
const quint16 UdpPortNumber = 7777;
const QString ServerAddress = "127.0.0.1";
const int TimerInterval = 100;
const quint32 MaxDelayedCount = 2;

const TestServerConfig serverConfig(TimerInterval, ServerAddress, TcpPortNumber, UdpPortNumber);
const TransportConfig transportConfig(MaxDelayedCount, ServerAddress, TcpPortNumber, UdpPortNumber);

ClientEntry CreateClientEntry(MessageType outgoingMessageType,
                              QVector<char> const &outgoingMessageData,
                              MessageType incomingMessageType,
                              QVector<char> const &incomingMessageData)
{
    return ClientEntry(CreateMessagePtr(outgoingMessageType, outgoingMessageData), CreateMessage(incomingMessageType, incomingMessageData));
}

ClientEntry CreateClientEntry(MessageType incomingMessageType, QVector<char> const &incomingMessageData)
{
    return ClientEntry(CreateMessage(incomingMessageType, incomingMessageData));
}

ClientEntry CreateClientDataEntry(quint8 packageNumber, quint8 calcNumber, QVector<char> const &data)
{
    return ClientEntry(CreateDataMessage(packageNumber, calcNumber, data));
}

}

TEST(TransportFunctionalTests, RequestResponse)
{
    QList<Message> serverData = {CreateMessage(MessageType::REQUEST, {66}),
                                 CreateMessage(MessageType::RESPONSE, {11, 12, 13})};
    TestServerRunner server(serverConfig);
    QList<ClientEntry> clientData = {CreateClientEntry(MessageType::REQUEST, {66}, MessageType::RESPONSE, {11, 12, 13})};
    server.Start(serverData);
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}

TEST(TransportFunctionalTests, Event)
{
    QList<Message> serverData = {CreateMessage(MessageType::EVENT, {66, 13, 66})};
    TestServerRunner server(serverConfig);
    QList<ClientEntry> clientData = {CreateClientEntry(MessageType::EVENT, {66, 13, 66})};
    server.Start(serverData);
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}

TEST(TransportFunctionalTests, RequestResponseEvent)
{
    QList<Message> serverData = {CreateMessage(MessageType::REQUEST, {66}),
                                 CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                 CreateMessage(MessageType::EVENT, {66, 13, 66})};
    TestServerRunner server(serverConfig);
    QList<ClientEntry> clientData = {CreateClientEntry(MessageType::REQUEST, {66}, MessageType::RESPONSE, {11, 12, 13}),
                                     CreateClientEntry(MessageType::EVENT, {66, 13, 66})};
    server.Start(serverData);
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}

TEST(TransportFunctionalTests, SingleData)
{
    QList<Message> serverData = {CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig);
    QList<ClientEntry> clientData = {CreateClientDataEntry(1, 0, {11, 10, 11})};
    server.Start(serverData);
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}

TEST(TransportFunctionalTests, SeveralData)
{
    QList<Message> serverData = {CreateDataMessage(1, 0, {11, 10, 11}),
                                 CreateDataMessage(2, 0, {13, 66})};
    TestServerRunner server(serverConfig);
    QList<ClientEntry> clientData = {CreateClientDataEntry(1, 0, {11, 10, 11}),
                                     CreateClientDataEntry(2, 0, {13, 66})};
    server.Start(serverData);
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}

TEST(TransportFunctionalTests, SeveralDataWithRepeats)
{
    QList<Message> serverData = {CreateDataMessage(1, 0, {11, 10, 11}),
                                 CreateDataMessage(2, 0, {13, 66}),
                                 CreateDataMessage(2, 0, {13, 66}),
                                 CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig);
    QList<ClientEntry> clientData = {CreateClientDataEntry(1, 0, {11, 10, 11}),
                                     CreateClientDataEntry(2, 0, {13, 66})};
    server.Start(serverData);
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}

TEST(TransportFunctionalTests, SeveralDataInWrongOrder)
{
    QList<Message> serverData = {CreateDataMessage(2, 0, {13, 66}),
                                 CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig);
    QList<ClientEntry> clientData = {CreateClientDataEntry(1, 0, {11, 10, 11}),
                                     CreateClientDataEntry(2, 0, {13, 66})};
    server.Start(serverData);
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}

TEST(TransportFunctionalTests, SeveralDataWithGap)
{
    QList<Message> serverData = {CreateDataMessage(1, 0, {11, 10, 11}),
                                 CreateDataMessage(3, 0, {13, 66})};
    TestServerRunner server(serverConfig);
    QList<ClientEntry> clientData = {CreateClientDataEntry(1, 0, {11, 10, 11})};
    server.Start(serverData);
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}

/*TEST(TransportFunctionalTests, TooManyDataInWrongOrder)
{
    QList<Message> serverData = {CreateDataMessage(2, 0, {11, 10, 11}),
                                 CreateDataMessage(3, 0, {13, 66}),
                                 CreateDataMessage(6, 0, {67})};
    TestServerRunner server(serverConfig);
    server.Start(serverData);
    ClientHandler::Check(transportConfig, {});
    server.Stop();
}*/

TEST(TransportFunctionalTests, RequestResponseSeveralEventsSeveralData)
{
    QList<Message> serverData = {CreateMessage(MessageType::REQUEST, {66}),
                                 CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                 CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                 CreateDataMessage(1, 0, {11, 10, 11}),
                                 CreateMessage(MessageType::EVENT, {99, 99}),
                                 CreateDataMessage(2, 0, {13, 66})};
    TestServerRunner server(serverConfig);
    QList<ClientEntry> clientData = {CreateClientEntry(MessageType::REQUEST, {66}, MessageType::RESPONSE, {11, 12, 13}),
                                     CreateClientEntry(MessageType::EVENT, {66, 13, 66}),
                                     CreateClientDataEntry(1, 0, {11, 10, 11}),
                                     CreateClientEntry(MessageType::EVENT, {99, 99}),
                                     CreateClientDataEntry(2, 0, {13, 66})};
    server.Start(serverData);
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}

TEST(TransportFunctionalTests, RequestResponseSeveralEventsSeveralDataWithRepeats)
{
    QList<Message> serverData = {CreateMessage(MessageType::REQUEST, {66}),
                                 CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                 CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                 CreateDataMessage(1, 0, {11, 10, 11}),
                                 CreateMessage(MessageType::EVENT, {99, 99}),
                                 CreateDataMessage(2, 0, {13, 66}),
                                 CreateDataMessage(2, 0, {13, 66}),
                                 CreateDataMessage(1, 0, {11, 10, 11}),};
    TestServerRunner server(serverConfig);
    QList<ClientEntry> clientData = {CreateClientEntry(MessageType::REQUEST, {66}, MessageType::RESPONSE, {11, 12, 13}),
                                     CreateClientEntry(MessageType::EVENT, {66, 13, 66}),
                                     CreateClientDataEntry(1, 0, {11, 10, 11}),
                                     CreateClientEntry(MessageType::EVENT, {99, 99}),
                                     CreateClientDataEntry(2, 0, {13, 66})};
    server.Start(serverData);
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}

TEST(TransportFunctionalTests, RequestResponseSeveralEventsSeveralDataInWrongOrder)
{
    QList<Message> serverData = {CreateMessage(MessageType::REQUEST, {66}),
                                 CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                 CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                 CreateDataMessage(2, 0, {13, 66}),
                                 CreateMessage(MessageType::EVENT, {99, 99}),
                                 CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig);
    QList<ClientEntry> clientData = {CreateClientEntry(MessageType::REQUEST, {66}, MessageType::RESPONSE, {11, 12, 13}),
                                     CreateClientEntry(MessageType::EVENT, {66, 13, 66}),
                                     CreateClientEntry(MessageType::EVENT, {99, 99}),
                                     CreateClientDataEntry(1, 0, {11, 10, 11}),
                                     CreateClientDataEntry(2, 0, {13, 66})};
    server.Start(serverData);
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}

/*TEST(TransportFunctionalTests, RequestResponseSeveralEventsTooManyDataInWrongOrder)
{
    QList<Message> serverData = {CreateMessage(MessageType::REQUEST, {66}),
                                 CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                 CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                 CreateDataMessage(2, 0, {11, 10, 11}),
                                 CreateDataMessage(3, 0, {13, 66}),
                                 CreateMessage(MessageType::EVENT, {99, 99}),
                                 CreateDataMessage(6, 0, {67})};
    TestServerRunner server(serverConfig);
    server.Start(serverData);
    QList<ClientEntry> clientData = {CreateClientEntry(MessageType::REQUEST, {66}, MessageType::RESPONSE, {11, 12, 13}),
                                     CreateClientEntry(MessageType::EVENT, {66, 13, 66}),
                                     CreateClientEntry(MessageType::EVENT, {99, 99}),
                                     // ???
                                     CreateDataMessage(1, 0, {13, 66}),};
    ClientHandler::Check(transportConfig, clientData);
    server.Stop();
}*/

}
