#include <memory>
#include <stdexcept>

#include "gtest/gtest.h"

#include "Common/CommonDefs.h"
#include "DelayedMessagesProcessor.h"
#include "DelayedMessagesProcessorHandler.h"
#include "EqualityOperators.h"
#include "IMessageCheckStrategy.h"
#include "MessageHelper.h"
#include "MessageInfo.h"
#include "SimpleMessageCheckStrategy.h"

namespace CalcApp
{

const quint32 MaxDelayedCount = 2;

class DelayedMessagesProcessorTests : public testing::Test
{
public:
    virtual void SetUp() override;
    virtual void TearDown() override;

protected:
    std::shared_ptr<DelayedMessagesProcessor> _processor;
    std::shared_ptr<DelayedMessagesProcessorHandler> _handler;

private:
    std::shared_ptr<IMessageCheckStrategy> _messageCheckStrategy;
};

void DelayedMessagesProcessorTests::SetUp()
{
    _messageCheckStrategy.reset(new SimpleMessageCheckStrategy(MaxDelayedCount));
    _processor = std::make_shared<DelayedMessagesProcessor>(_messageCheckStrategy.get());
    _handler = std::make_shared<DelayedMessagesProcessorHandler>(_processor);
}

void DelayedMessagesProcessorTests::TearDown()
{
    _handler.reset();
    _processor.reset();
    _messageCheckStrategy.reset();
}

TEST_F(DelayedMessagesProcessorTests, AddDelayedMessage)
{
    const int repeatedAddCount = 3;
    for (int i = 0; i < repeatedAddCount; ++i)
    {
        ASSERT_NO_THROW(_processor.get()->AddDelayedMessage(MessageInfo(5, 0), CreateDataMessage(5, 0, {10, 11, 12})));
        ASSERT_FALSE(_handler.get()->MessageProcessFail);
    }
    for (int i = 0; i < repeatedAddCount; ++i)
    {
        ASSERT_NO_THROW(_processor.get()->AddDelayedMessage(MessageInfo(3, 0), CreateDataMessage(3, 0, {2, 3})));
        ASSERT_FALSE(_handler.get()->MessageProcessFail);
    }
    ASSERT_NO_THROW(_processor.get()->AddDelayedMessage(MessageInfo(9, 0), CreateDataMessage(9, 0, {6, 9, 13})));
    ASSERT_TRUE(_handler.get()->MessageProcessFail);
    _handler.get()->MessageProcessFail = false;
    ASSERT_NO_THROW(_processor.get()->DeliverMessage(MessageInfo(2, 0)));
    ASSERT_FALSE(_handler.get()->MessageProcessFail);
    for (int i = 0; i < repeatedAddCount; ++i)
    {
        ASSERT_NO_THROW(_processor.get()->AddDelayedMessage(MessageInfo(9, 0), CreateDataMessage(9, 0, {4, 1, 2})));
        ASSERT_FALSE(_handler.get()->MessageProcessFail);
    }
}

TEST_F(DelayedMessagesProcessorTests, CanDeliverMessage)
{
    ASSERT_FALSE(_processor.get()->CanDeliverMessage(MessageInfo(1, 0)));
    ASSERT_NO_THROW(_processor.get()->AddDelayedMessage(MessageInfo(5, 0), CreateDataMessage(5, 0, {13})));
    ASSERT_FALSE(_handler.get()->MessageProcessFail);
    ASSERT_FALSE(_processor.get()->CanDeliverMessage(MessageInfo(1, 0)));
    ASSERT_TRUE(_processor.get()->CanDeliverMessage(MessageInfo(4, 0)));
}

TEST_F(DelayedMessagesProcessorTests, DeliverMessage)
{
    ASSERT_THROW(_processor.get()->DeliverMessage(MessageInfo(1, 0)), std::logic_error);
    ASSERT_NO_THROW(_processor.get()->AddDelayedMessage(MessageInfo(3, 0), CreateDataMessage(3, 0, {6, 6, 6})));
    ASSERT_THROW(_processor.get()->DeliverMessage(MessageInfo(1, 0)), std::logic_error);
    ASSERT_EQ(CreateMessageData(3, 0, {6, 6, 6}), _processor.get()->DeliverMessage(MessageInfo(2, 0)));
    ASSERT_THROW(_processor.get()->DeliverMessage(MessageInfo(2, 0)), std::logic_error);
}

TEST_F(DelayedMessagesProcessorTests, Lifecycle)
{
    ASSERT_FALSE(_processor.get()->CanDeliverMessage(MessageInfo(1, 0)));
    ASSERT_THROW(_processor.get()->DeliverMessage(MessageInfo(1, 0)), std::logic_error);
    ASSERT_NO_THROW(_processor.get()->AddDelayedMessage(MessageInfo(5, 0), CreateDataMessage(5, 0, {10, 12})));
    ASSERT_FALSE(_handler.get()->MessageProcessFail);
    ASSERT_NO_THROW(_processor.get()->AddDelayedMessage(MessageInfo(3, 0), CreateDataMessage(3, 0, {4, 11, 5})));
    ASSERT_FALSE(_handler.get()->MessageProcessFail);
    ASSERT_NO_THROW(_processor.get()->AddDelayedMessage(MessageInfo(9, 0), CreateDataMessage(9, 0, {3, 2, 1})));
    ASSERT_TRUE(_handler.get()->MessageProcessFail);
    _handler.get()->MessageProcessFail = false;
    ASSERT_FALSE(_processor.get()->CanDeliverMessage(MessageInfo(1, 0)));
    ASSERT_THROW(_processor.get()->DeliverMessage(MessageInfo(1, 0)), std::logic_error);
    ASSERT_TRUE(_processor.get()->CanDeliverMessage(MessageInfo(2, 0)));
    ASSERT_EQ(CreateMessageData(3, 0, {4, 11, 5}), _processor.get()->DeliverMessage(MessageInfo(2, 0)));
    ASSERT_NO_THROW(_processor.get()->AddDelayedMessage(MessageInfo(10, 0), CreateDataMessage(10, 0, {2, 2, 2})));
    ASSERT_FALSE(_handler.get()->MessageProcessFail);
}

}
