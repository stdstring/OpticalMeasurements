#include <QList>

#include <memory>

#include "gtest/gtest.h"

#include "Message.h"
#include "MessageHelper.h"
#include "TestServer.h"
#include "TransportConfig.h"

namespace CalcApp
{

TEST(TransportFunctionalTests, Test1)
{
    QList<Message> serverData = {CreateMessage(MessageType::RESPONSE, {11, 12, 13})};
    TestServerRunner server(serverData);
    QList<ClientEntry> clientData = {ClientEntry(CreateMessagePtr(MessageType::REQUEST, {66}), CreateMessage(MessageType::RESPONSE, {11, 12, 13}))};
    // TODO (std_string) : think about this
    TransportConfig config(2, "127.0.0.1", 6666, 7777);
    server.Start();
    ClientHandler::Check(config, clientData);
    server.Stop();
}

/*TEST(TransportFunctionalTests, Test2)
{
    QList<Message> serverData = {CreateMessage(MessageType::RESPONSE, {11, 12, 13})};
    TestServerRunner server(serverData);
    QList<ClientEntry> clientData = {ClientEntry(CreateMessagePtr(MessageType::REQUEST, {66}), CreateMessage(MessageType::RESPONSE, {11, 12, 14}))};
    // TODO (std_string) : think about this
    TransportConfig config(2, "127.0.0.1", 6666, 7777);
    server.Start();
    ClientHandler::Check(config, clientData);
    server.Stop();
}*/

}
