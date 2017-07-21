#include <QList>

#include <memory>

#include "gtest/gtest.h"

#include "Common/CommonDefs.h"
#include "Common/Logger/ILogger.h"
#include "Common/Logger/NullLogger.h"
#include "Common/Message.h"
#include "Common/TransportConfig.h"
#include "TestServerCore/TestServerRunner.h"
#include "TestServerCore/TestServerConfig.h"
#include "ClientHandler.h"
#include "MessageHelper.h"

namespace CalcApp
{

/*namespace
{

// TODO (std_string) : think about location of this data
const quint16 TcpPortNumber = 6666;
const quint16 UdpPortNumber = 7777;
const QString ServerAddress = "127.0.0.1";
const int TimerInterval = 100;
const quint32 MaxDelayedCount = 2;

const TestServerConfig serverConfig(TimerInterval, ServerAddress, TcpPortNumber, UdpPortNumber);
const TransportConfig transportConfig(MaxDelayedCount, ServerAddress, TcpPortNumber, UdpPortNumber);

LoggerPtr logger(new NullLogger());

}

TEST(TransportFunctionalTests, RequestResponse)
{
    QList<MessagePtr> messages = {CreateMessage(MessageType::REQUEST, {66}),
                                  CreateMessage(MessageType::RESPONSE, {11, 12, 13})};
    TestServerRunner server(serverConfig, logger);
    server.Start(messages);
    ClientHandler::Check(transportConfig, messages);
    server.Stop();
}

TEST(TransportFunctionalTests, Event)
{
    QList<MessagePtr> messages = {CreateMessage(MessageType::EVENT, {66, 13, 66})};
    TestServerRunner server(serverConfig, logger);
    server.Start(messages);
    ClientHandler::Check(transportConfig, messages);
    server.Stop();
}

TEST(TransportFunctionalTests, RequestResponseEvent)
{
    QList<MessagePtr> messages = {CreateMessage(MessageType::REQUEST, {66}),
                                  CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                  CreateMessage(MessageType::EVENT, {66, 13, 66})};
    TestServerRunner server(serverConfig, logger);
    server.Start(messages);
    ClientHandler::Check(transportConfig, messages);
    server.Stop();
}

TEST(TransportFunctionalTests, SingleData)
{
    QList<MessagePtr> messages = {CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig, logger);
    server.Start(messages);
    ClientHandler::Check(transportConfig, messages);
    server.Stop();
}

TEST(TransportFunctionalTests, SeveralData)
{
    QList<MessagePtr> messages = {CreateDataMessage(1, 0, {11, 10, 11}), CreateDataMessage(2, 0, {13, 66})};
    TestServerRunner server(serverConfig, logger);
    server.Start(messages);
    ClientHandler::Check(transportConfig, messages);
    server.Stop();
}

TEST(TransportFunctionalTests, SeveralDataWithRepeats)
{
    QList<MessagePtr> serverMessages = {CreateDataMessage(1, 0, {11, 10, 11}),
                                        CreateDataMessage(2, 0, {13, 66}),
                                        CreateDataMessage(2, 0, {13, 66}),
                                        CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig, logger);
    QList<MessagePtr> clientMessages = {CreateDataMessage(1, 0, {11, 10, 11}),
                                        CreateDataMessage(2, 0, {13, 66})};
    server.Start(serverMessages);
    ClientHandler::Check(transportConfig, clientMessages);
    server.Stop();
}

TEST(TransportFunctionalTests, SeveralDataInWrongOrder)
{
    QList<MessagePtr> serverMessages = {CreateDataMessage(2, 0, {13, 66}), CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig, logger);
    QList<MessagePtr> clientMessages = {CreateDataMessage(1, 0, {11, 10, 11}), CreateDataMessage(2, 0, {13, 66})};
    server.Start(serverMessages);
    ClientHandler::Check(transportConfig, clientMessages);
    server.Stop();
}

TEST(TransportFunctionalTests, SeveralDataWithGap)
{
    QList<MessagePtr> serverMessages = {CreateDataMessage(1, 0, {11, 10, 11}), CreateDataMessage(3, 0, {13, 66})};
    TestServerRunner server(serverConfig, logger);
    QList<MessagePtr> clientMessages = {CreateDataMessage(1, 0, {11, 10, 11})};
    server.Start(serverMessages);
    ClientHandler::Check(transportConfig, clientMessages);
    server.Stop();
}

//TEST(TransportFunctionalTests, TooManyDataInWrongOrder)
//{
//    QList<MessagePtr> messages = {CreateDataMessage(2, 0, {11, 10, 11}),
//                                  CreateDataMessage(3, 0, {13, 66}),
//                                  CreateDataMessage(6, 0, {67})};
//    TestServerRunner server(serverConfig, logger);
//    server.Start(messages);
//    ClientHandler::Check(transportConfig, {});
//    server.Stop();
//}

TEST(TransportFunctionalTests, RequestResponseSeveralEventsSeveralData)
{
    QList<MessagePtr> messages = {CreateMessage(MessageType::REQUEST, {66}),
                                  CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                  CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                  CreateDataMessage(1, 0, {11, 10, 11}),
                                  CreateMessage(MessageType::EVENT, {99, 99}),
                                  CreateDataMessage(2, 0, {13, 66})};
    TestServerRunner server(serverConfig, logger);
    server.Start(messages);
    ClientHandler::Check(transportConfig, messages);
    server.Stop();
}

TEST(TransportFunctionalTests, RequestResponseSeveralEventsSeveralDataWithRepeats)
{
    QList<MessagePtr> serverMessages = {CreateMessage(MessageType::REQUEST, {66}),
                                        CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                        CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                        CreateDataMessage(1, 0, {11, 10, 11}),
                                        CreateMessage(MessageType::EVENT, {99, 99}),
                                        CreateDataMessage(2, 0, {13, 66}),
                                        CreateDataMessage(2, 0, {13, 66}),
                                        CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig, logger);
    QList<MessagePtr> clientMessages = {CreateMessage(MessageType::REQUEST, {66}),
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
    QList<MessagePtr> serverMessages = {CreateMessage(MessageType::REQUEST, {66}),
                                        CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                        CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                        CreateDataMessage(2, 0, {13, 66}),
                                        CreateMessage(MessageType::EVENT, {99, 99}),
                                        CreateDataMessage(1, 0, {11, 10, 11})};
    TestServerRunner server(serverConfig, logger);
    QList<MessagePtr> clientMessages = {CreateMessage(MessageType::REQUEST, {66}),
                                        CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
                                        CreateMessage(MessageType::EVENT, {66, 13, 66}),
                                        CreateMessage(MessageType::EVENT, {99, 99}),
                                        CreateDataMessage(1, 0, {11, 10, 11}),
                                        CreateDataMessage(2, 0, {13, 66})};
    server.Start(serverMessages);
    ClientHandler::Check(transportConfig, clientMessages);
    server.Stop();
}

//TEST(TransportFunctionalTests, RequestResponseSeveralEventsTooManyDataInWrongOrder)
//{
//    QList<MessagePtr> serverMessages = {CreateMessage(MessageType::REQUEST, {66}),
//                                        CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
//                                        CreateMessage(MessageType::EVENT, {66, 13, 66}),
//                                        CreateDataMessage(2, 0, {11, 10, 11}),
//                                        CreateDataMessage(3, 0, {13, 66}),
//                                        CreateMessage(MessageType::EVENT, {99, 99}),
//                                        CreateDataMessage(6, 0, {67})};
//    TestServerRunner server(serverConfig);
//    server.Start(serverMessages, logger);
//    QList<MessagePtr> clientMessages = {CreateMessage(MessageType::REQUEST, {66}),
//                                        CreateMessage(MessageType::RESPONSE, {11, 12, 13}),
//                                        CreateMessage(MessageType::EVENT, {66, 13, 66}),
//                                        CreateMessage(MessageType::EVENT, {99, 99}),
//                                        // ???
//                                        CreateDataMessage(1, 0, {13, 66})};
//    ClientHandler::Check(transportConfig, clientMessages);
//    server.Stop();
//}*/

}
