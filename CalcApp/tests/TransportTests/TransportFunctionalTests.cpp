#include <QCoreApplication>
#include <QList>

#include "gtest/gtest.h"

#include "Message.h"
#include "MessageHelper.h"
#include "TestServer.h"
#include "TransportConfig.h"

namespace CalcApp
{

TEST(TransportFunctionalTests, Test1)
{
    int argc = 0;
    char *argv[] = {};
    QCoreApplication app(argc, argv);

    QList<Message> serverData = {CreateMessage(MessageType::RESPONSE, {11, 12, 13})};
    TestServerRunner server(serverData);
    QList<ClientEntry> clientData = {ClientEntry([](ITransport *transport){ transport->Send(CreateMessage(MessageType::REQUEST, {66})); }, CreateMessage(MessageType::RESPONSE, {11, 12, 13}))};
    // TODO (std_string) : think about this
    TransportConfig config(2, "127.0.0.1", 6666, 7777);
    //TransportLowLevel transportLowLevel(config);
    //SimpleMessageCheckStrategy messageCheckStrategy(config.MaxDelayedCount);
    //Transport transport(&transportLowLevel, &messageCheckStrategy);
    server.Start();
    ClientHandler::Check(config, clientData);
    server.Stop();
}

/*TEST(TransportFunctionalTests, Test2)
{
    int argc = 0;
    char *argv[] = {};
    QCoreApplication app(argc, argv);

    QList<Message> serverData = {CreateMessage(MessageType::RESPONSE, {11, 12, 13})};
    TestServerRunner server(serverData);
    QList<ClientEntry> clientData = {ClientEntry([](ITransport *transport){ transport->Send(CreateMessage(MessageType::REQUEST, {66})); }, CreateMessage(MessageType::RESPONSE, {11, 12, 14}))};
    // TODO (std_string) : think about this
    TransportConfig config(2, "127.0.0.1", 6666, 7777);
    //TransportLowLevel transportLowLevel(config);
    //SimpleMessageCheckStrategy messageCheckStrategy(config.MaxDelayedCount);
    //Transport transport(&transportLowLevel, &messageCheckStrategy);
    server.Start();
    ClientHandler::Check(config, clientData);
    server.Stop();
}*/

}
