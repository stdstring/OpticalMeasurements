#include <QByteArray>

#include "gtest/gtest.h"

#include "EqualityOperators.h"
#include "MessageHelper.h"
#include "MessageInfo.h"
#include "MessageInfoFactory.h"

namespace CalcApp
{

TEST(MessageInfoFactoryTests, Create)
{
    ASSERT_EQ(MessageInfo(1, 0), CreateMessageInfo(CreateMessage(MessageType::DATA, {0, 0, 0, 1, 0, 0, 0, 0, 1, 2})));
    ASSERT_EQ(MessageInfo(4, 2), CreateMessageInfo(CreateMessage(MessageType::DATA, {0, 0, 0, 4, 0, 0, 0, 2, 10, 11, 12, 13, 14})));
    ASSERT_EQ(MessageInfo(11, 66), CreateMessageInfo(CreateMessage(MessageType::DATA, {0, 0, 0, 11, 0, 0, 0, 66})));
    ASSERT_EQ(MessageInfo(257, 256), CreateMessageInfo(CreateMessage(MessageType::DATA, {0, 0, 1, 1, 0, 0, 1, 0, 33})));
}

}
