#include <QByteArray>

#include "gtest/gtest.h"

#include "EqualityOperators.h"
#include "Message.h"
#include "MessageInfo.h"
#include "MessageInfoFactory.h"

namespace CalcApp
{

TEST(MessageInfoFactoryTests, Create)
{
    ASSERT_EQ(MessageInfo(0, 0), CreateMessageInfo(Message(MessageType::DATA, QByteArray())));
}

}
