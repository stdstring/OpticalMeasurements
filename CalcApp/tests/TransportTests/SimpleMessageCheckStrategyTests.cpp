#include "gtest/gtest.h"

#include "MessageHelper.h"
#include "MessageInfo.h"
#include "SimpleMessageCheckStrategy.h"

namespace CalcApp
{

TEST(SimpleMessageCheckStrategyTests, Check)
{
    SimpleMessageCheckStrategy strategy(2);
    ASSERT_TRUE(strategy.Check(MessageInfo(10, 1), {}));
    ASSERT_TRUE(strategy.Check(MessageInfo(10, 1), {CreateMessageData(7, 2)}));
    ASSERT_FALSE(strategy.Check(MessageInfo(10, 1), {CreateMessageData(7, 2), CreateMessageData(6, 1)}));
}

TEST(SimpleMessageCheckStrategyTests, CheckZeroMaxDelayedCount)
{
    SimpleMessageCheckStrategy strategy(0);
    ASSERT_FALSE(strategy.Check(MessageInfo(10, 1), {}));
}

}
