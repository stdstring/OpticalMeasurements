#include "gtest/gtest.h"

#include "MessageInfo.h"
#include "MessageValidation.h"

namespace CalcApp
{

TEST(MessageValidationTests, ProcessMessage)
{
    ASSERT_EQ(MessageValidationResult::PROCESS, IsMessageValid(MessageInfo(1, 0), MessageInfo()));
    ASSERT_EQ(MessageValidationResult::PROCESS, IsMessageValid(MessageInfo(1, 1), MessageInfo()));
    ASSERT_EQ(MessageValidationResult::PROCESS, IsMessageValid(MessageInfo(3, 0), MessageInfo(2, 0)));
    ASSERT_EQ(MessageValidationResult::PROCESS, IsMessageValid(MessageInfo(3, 1), MessageInfo(2, 0)));
}

TEST(MessageValidationTests, SkipMessage)
{
    ASSERT_EQ(MessageValidationResult::SKIP, IsMessageValid(MessageInfo(0, 0), MessageInfo()));
    ASSERT_EQ(MessageValidationResult::SKIP, IsMessageValid(MessageInfo(0, 1), MessageInfo()));
    ASSERT_EQ(MessageValidationResult::SKIP, IsMessageValid(MessageInfo(2, 0), MessageInfo(2, 0)));
    ASSERT_EQ(MessageValidationResult::SKIP, IsMessageValid(MessageInfo(2, 1), MessageInfo(2, 0)));
    ASSERT_EQ(MessageValidationResult::SKIP, IsMessageValid(MessageInfo(1, 0), MessageInfo(2, 0)));
    ASSERT_EQ(MessageValidationResult::SKIP, IsMessageValid(MessageInfo(1, 1), MessageInfo(2, 0)));
}

TEST(MessageValidationTests, DelayMessage)
{
    ASSERT_EQ(MessageValidationResult::DELAY, IsMessageValid(MessageInfo(2, 0), MessageInfo()));
    ASSERT_EQ(MessageValidationResult::DELAY, IsMessageValid(MessageInfo(2, 1), MessageInfo()));
    ASSERT_EQ(MessageValidationResult::DELAY, IsMessageValid(MessageInfo(4, 0), MessageInfo()));
    ASSERT_EQ(MessageValidationResult::DELAY, IsMessageValid(MessageInfo(4, 1), MessageInfo()));
    ASSERT_EQ(MessageValidationResult::DELAY, IsMessageValid(MessageInfo(4, 0), MessageInfo(2, 0)));
    ASSERT_EQ(MessageValidationResult::DELAY, IsMessageValid(MessageInfo(4, 1), MessageInfo(2, 0)));
    ASSERT_EQ(MessageValidationResult::DELAY, IsMessageValid(MessageInfo(6, 0), MessageInfo(2, 0)));
    ASSERT_EQ(MessageValidationResult::DELAY, IsMessageValid(MessageInfo(6, 1), MessageInfo(2, 0)));
}

}
