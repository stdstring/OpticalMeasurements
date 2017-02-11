#include <memory>
#include <stdexcept>
#include <vector>

#include <QByteArray>
#include <QObject>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "EqualityOperators.h"
#include "IMessageCheckStrategy.h"
#include "ITransport.h"
#include "Message.h"
#include "MessageHelper.h"
#include "SimpleMessageCheckStrategy.h"
#include "Transport.h"
#include "TransportSignalHandler.h"

namespace CalcApp
{

class TransportLowLevelMock : public ITransport
{
public:
    MOCK_METHOD0(Connect, void());
    MOCK_METHOD1(Send, void(Message const &message));
};

const quint32 MaxDelayedCount = 2;

class TransportTests : public testing::Test
{
public:
    virtual void SetUp() override;
    virtual void TearDown() override;

protected:
    std::shared_ptr<IMessageCheckStrategy> _messageCheckStrategy;
    std::shared_ptr<testing::StrictMock<TransportLowLevelMock>> _transportLowLevel;
};

void TransportTests::SetUp()
{
    _messageCheckStrategy.reset(new SimpleMessageCheckStrategy(MaxDelayedCount));
    _transportLowLevel.reset(new testing::StrictMock<TransportLowLevelMock>());
}

void TransportTests::TearDown()
{
    _messageCheckStrategy.reset();
    _transportLowLevel.reset();
}

TEST_F(TransportTests, Connect)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    ASSERT_EQ(signalHandler.Messages.size(), 0);
}

TEST_F(TransportTests, SendWithoutResponse)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST))).Times(1);
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    transport.Send(CreateMessage(MessageType::REQUEST));
    ASSERT_EQ(signalHandler.Messages.size(), 0);
}

TEST_F(TransportTests, SendWithResponse)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST)))
            .Times(1)
            .WillOnce(testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->ResponseReceived(CreateMessage(MessageType::RESPONSE)); }));
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    transport.Send(CreateMessage(MessageType::REQUEST));
    ASSERT_EQ(signalHandler.Messages.size(), 1);
    ASSERT_EQ(signalHandler.Messages[0], CreateMessage(MessageType::RESPONSE));
}

TEST_F(TransportTests, SendWithResponseAndEvent)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST)))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->ResponseReceived(CreateMessage(MessageType::RESPONSE)); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->EventReceived(CreateMessage(MessageType::EVENT)); })));
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    transport.Send(CreateMessage(MessageType::REQUEST));
    ASSERT_EQ(signalHandler.Messages.size(), 2);
    ASSERT_EQ(signalHandler.Messages[0], CreateMessage(MessageType::RESPONSE));
    ASSERT_EQ(signalHandler.Messages[1], CreateMessage(MessageType::EVENT));
}

TEST_F(TransportTests, SendWithResponseAndData)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST)))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->ResponseReceived(CreateMessage(MessageType::RESPONSE)); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateMessage(1, 0)); })));
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    transport.Send(CreateMessage(MessageType::REQUEST));
    ASSERT_EQ(signalHandler.Messages.size(), 2);
    ASSERT_EQ(signalHandler.Messages[0], CreateMessage(MessageType::RESPONSE));
    ASSERT_EQ(signalHandler.Messages[1], CreateMessage(1, 0));
}

TEST_F(TransportTests, UnorderedData)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST)))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->ResponseReceived(CreateMessage(MessageType::RESPONSE)); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateMessage(2, 0)); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateMessage(1, 0)); })));
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    transport.Send(CreateMessage(MessageType::REQUEST));
    ASSERT_EQ(signalHandler.Messages.size(), 3);
    ASSERT_EQ(signalHandler.Messages[0], CreateMessage(MessageType::RESPONSE));
    ASSERT_EQ(signalHandler.Messages[1], CreateMessage(1, 0));
    ASSERT_EQ(signalHandler.Messages[2], CreateMessage(2, 0));
}

TEST_F(TransportTests, DelayedData)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST)))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->ResponseReceived(CreateMessage(MessageType::RESPONSE)); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateMessage(9, 0)); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateMessage(1, 0)); })));
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    transport.Send(CreateMessage(MessageType::REQUEST));
    ASSERT_EQ(signalHandler.Messages.size(), 2);
    ASSERT_EQ(signalHandler.Messages[0], CreateMessage(MessageType::RESPONSE));
    ASSERT_EQ(signalHandler.Messages[1], CreateMessage(1, 0));
}

TEST_F(TransportTests, DelayedDataGreaterMaxDelayedCount)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST)))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->ResponseReceived(CreateMessage(MessageType::RESPONSE)); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateMessage(9, 0)); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateMessage(4, 0)); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateMessage(3, 0)); })));
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    ASSERT_THROW(transport.Send(CreateMessage(MessageType::REQUEST)), std::logic_error);
    ASSERT_EQ(signalHandler.Messages.size(), 1);
    ASSERT_EQ(signalHandler.Messages[0], CreateMessage(MessageType::RESPONSE));
}

}
