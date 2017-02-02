#include <QByteArray>

#include <stdexcept>

#include "gtest/gtest.h"

#include "DelayedMessagesProcessor.h"
#include "Message.h"
#include "MessageInfo.h"
#include "SimpleMessageCheckStrategy.h"

namespace CalcApp
{

// TODO (std_string) : move into common library
bool operator ==(const MessageInfo &left, const MessageInfo &right)
{
    return (left.GetPackageNumber() == right.GetPackageNumber()) && (left.GetCalcNumber() == right.GetCalcNumber());
}

// TODO (std_string) : move into common library
bool operator ==(const Message &left, const Message &right)
{
    return (left.GetType() == right.GetType()) && (left.GetData() == right.GetData());
}

TEST(DelayedMessagesProcessorTests, Lifecycle)
{
    const quint32 maxDelayedCount = 2;
    const int repeatedAddCount = 3;
    SimpleMessageCheckStrategy messageCheckStrategy(maxDelayedCount);
    DelayedMessagesProcessor processor(&messageCheckStrategy);
    ASSERT_FALSE(processor.CanDeliverMessage(MessageInfo(1, 0)));
    ASSERT_THROW(processor.DeliverMessage(MessageInfo(1, 0)), std::logic_error);
    for (int i = 0; i < repeatedAddCount; ++i)
        ASSERT_NO_THROW(processor.AddDelayedMessage(MessageInfo(5, 0), Message(MessageType::DATA, QByteArray())));
    for (int i = 0; i < repeatedAddCount; ++i)
        ASSERT_NO_THROW(processor.AddDelayedMessage(MessageInfo(3, 0), Message(MessageType::DATA, QByteArray())));
    ASSERT_THROW(processor.AddDelayedMessage(MessageInfo(9, 0), Message(MessageType::DATA, QByteArray())), std::logic_error);
    ASSERT_FALSE(processor.CanDeliverMessage(MessageInfo(1, 0)));
    ASSERT_THROW(processor.DeliverMessage(MessageInfo(1, 0)), std::logic_error);
    ASSERT_TRUE(processor.CanDeliverMessage(MessageInfo(2, 0)));
    MessageData expectedData(MessageInfo(3, 0), Message(MessageType::DATA, QByteArray()));
    ASSERT_EQ(expectedData, processor.DeliverMessage(MessageInfo(2, 0)));
}

}
