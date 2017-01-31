#include <QByteArray>
#include <QList>

#include "gtest/gtest.h"

#include "Message.h"
#include "MessageInfo.h"
#include "SimpleMessageCheckStrategy.h"

namespace CalcApp
{

namespace
{

MessageData CreateMessageData(quint32 packageNumber)
{
    return MessageData(MessageInfo(packageNumber, 0), Message(MessageType::DATA, QByteArray()));
}

}

TEST(SimpleMessageCheckStrategyTests, Check)
{
    SimpleMessageCheckStrategy strategy(2);
    ASSERT_TRUE(strategy.Check(MessageInfo(10, 0), {}));
    ASSERT_TRUE(strategy.Check(MessageInfo(10, 0), {CreateMessageData(7)}));
    ASSERT_FALSE(strategy.Check(MessageInfo(10, 0), {CreateMessageData(7), CreateMessageData(6)}));
}

TEST(SimpleMessageCheckStrategyTests, CheckZeroMaxDelayedCount)
{
    SimpleMessageCheckStrategy strategy(0);
    ASSERT_FALSE(strategy.Check(MessageInfo(10, 0), {}));
}

}
