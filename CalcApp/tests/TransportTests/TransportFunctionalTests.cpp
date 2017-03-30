#include <QList>

#include "gtest/gtest.h"

#include "Common/Message.h"
#include "Common/TransportConfig.h"
#include "TestServerCore/TestServerRunner.h"
#include "TestServerCore/TestServerConfig.h"
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

}

TEST(TransportFunctionalTests, RequestResponse)
{
    QList<Message> messages = {CreateMessage(MessageType::REQUEST, {66}),
                               CreateMessage(MessageType::RESPONSE, {11, 12, 13})};
    TestServerRunner server(serverConfig);
    server.Start(messages);
    ClientHandler::Check(transportConfig, messages);
    server.Stop();
}

TEST(TransportFunctionalTests, Event)
{
    QList<Message> messages = {CreateMessage(MessageType::EVENT, {66, 13, 66})};
    TestServerRunner server(serverConfig);
    server.Start(messages);
    ClientHandler::Check(transportConfig, messages);
    server.Stop();
}

TEST(TransportFunctionalTests, RequestResponseEvent)
{
    QList<Message> messages = {CreateMessage(MessageType::REQUEST, {66}),
                               CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                               CreateMessage(MessageType::EVENT, {66, 13, 66})};
    TestServerRunner server(serverConfig);
    server.Start(messages);
    ClientHandler::Check(transportConfig, messages);
    server.Stop();
}

TEST(TransportFunctionalTests, SingleData)
{
    QList<Message> messages = {CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig);
    server.Start(messages);
    ClientHandler::Check(transportConfig, messages);
    server.Stop();
}

TEST(TransportFunctionalTests, SeveralData)
{
    QList<Message> messages = {CreateDataMessage(1, 0, {11, 10, 11}), CreateDataMessage(2, 0, {13, 66})};
    TestServerRunner server(serverConfig);
    server.Start(messages);
    ClientHandler::Check(transportConfig, messages);
    server.Stop();
}

TEST(TransportFunctionalTests, SeveralDataWithRepeats)
{
    QList<Message> serverMessages = {CreateDataMessage(1, 0, {11, 10, 11}),
                                     CreateDataMessage(2, 0, {13, 66}),
                                     CreateDataMessage(2, 0, {13, 66}),
                                     CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig);
    QList<Message> clientMessages = {CreateDataMessage(1, 0, {11, 10, 11}),
                                     CreateDataMessage(2, 0, {13, 66})};
    server.Start(serverMessages);
    ClientHandler::Check(transportConfig, clientMessages);
    server.Stop();
}

TEST(TransportFunctionalTests, SeveralDataInWrongOrder)
{
    QList<Message> serverMessages = {CreateDataMessage(2, 0, {13, 66}), CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig);
    QList<Message> clientMessages = {CreateDataMessage(1, 0, {11, 10, 11}), CreateDataMessage(2, 0, {13, 66})};
    server.Start(serverMessages);
    ClientHandler::Check(transportConfig, clientMessages);
    server.Stop();
}

TEST(TransportFunctionalTests, SeveralDataWithGap)
{
    QList<Message> serverMessages = {CreateDataMessage(1, 0, {11, 10, 11}), CreateDataMessage(3, 0, {13, 66})};
    TestServerRunner server(serverConfig);
    QList<Message> clientMessages = {CreateDataMessage(1, 0, {11, 10, 11})};
    server.Start(serverMessages);
    ClientHandler::Check(transportConfig, clientMessages);
    server.Stop();
}

/*TEST(TransportFunctionalTests, TooManyDataInWrongOrder)
{
    QList<Message> messages = {CreateDataMessage(2, 0, {11, 10, 11}),
                               CreateDataMessage(3, 0, {13, 66}),
                               CreateDataMessage(6, 0, {67})};
    TestServerRunner server(serverConfig);
    server.Start(messages);
    ClientHandler::Check(transportConfig, {});
    server.Stop();
}*/

TEST(TransportFunctionalTests, RequestResponseSeveralEventsSeveralData)
{
    QList<Message> messages = {CreateMessage(MessageType::REQUEST, {66}),
                               CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                               CreateMessage(MessageType::EVENT, {66, 13, 66}),
                               CreateDataMessage(1, 0, {11, 10, 11}),
                               CreateMessage(MessageType::EVENT, {99, 99}),
                               CreateDataMessage(2, 0, {13, 66})};
    TestServerRunner server(serverConfig);
    server.Start(messages);
    ClientHandler::Check(transportConfig, messages);
    server.Stop();
}

TEST(TransportFunctionalTests, RequestResponseSeveralEventsSeveralDataWithRepeats)
{
    QList<Message> serverMessages = {CreateMessage(MessageType::REQUEST, {66}),
                                     CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                     CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                     CreateDataMessage(1, 0, {11, 10, 11}),
                                     CreateMessage(MessageType::EVENT, {99, 99}),
                                     CreateDataMessage(2, 0, {13, 66}),
                                     CreateDataMessage(2, 0, {13, 66}),
                                     CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig);
    QList<Message> clientMessages = {CreateMessage(MessageType::REQUEST, {66}),
                                     CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                     CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                     CreateDataMessage(1, 0, {11, 10, 11}),
                                     CreateMessage(MessageType::EVENT, {99, 99}),
                                     CreateDataMessage(2, 0, {13, 66})};
    server.Start(serverMessages);
    ClientHandler::Check(transportConfig, clientMessages);
    server.Stop();
}

TEST(TransportFunctionalTests, RequestResponseSeveralEventsSeveralDataInWrongOrder)
{
    QList<Message> serverMessages = {CreateMessage(MessageType::REQUEST, {66}),
                                     CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                     CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                     CreateDataMessage(2, 0, {13, 66}),
                                     CreateMessage(MessageType::EVENT, {99, 99}),
                                     CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig);
    QList<Message> clientMessages = {CreateMessage(MessageType::REQUEST, {66}),
                                     CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                     CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                     CreateMessage(MessageType::EVENT, {99, 99}),
                                     CreateDataMessage(1, 0, {11, 10, 11}),
                                     CreateDataMessage(2, 0, {13, 66})};
    server.Start(serverMessages);
    ClientHandler::Check(transportConfig, clientMessages);
    server.Stop();
}

/*TEST(TransportFunctionalTests, RequestResponseSeveralEventsTooManyDataInWrongOrder)
{
    QList<Message> serverMessages = {CreateMessage(MessageType::REQUEST, {66}),
                                     CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                     CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                     CreateDataMessage(2, 0, {11, 10, 11}),
                                     CreateDataMessage(3, 0, {13, 66}),
                                     CreateMessage(MessageType::EVENT, {99, 99}),
                                     CreateDataMessage(6, 0, {67})};
    TestServerRunner server(serverConfig);
    server.Start(serverMessages);
    QList<Message> clientMessages = {CreateMessage(MessageType::REQUEST, {66}),
                                     CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                     CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                     CreateMessage(MessageType::EVENT, {99, 99}),
                                     // ???
                                     CreateDataMessage(1, 0, {13, 66})};
    ClientHandler::Check(transportConfig, clientMessages);
    server.Stop();
}*/

}
