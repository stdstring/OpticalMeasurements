#include <memory>
#include <stdexcept>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Common/CommonDefs.h"
#include "Common/ITransport.h"
#include "Common/Message.h"
#include "EqualityOperators.h"
#include "IMessageCheckStrategy.h"
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
    MOCK_METHOD1(Send, void(MessagePtr message));
    MOCK_METHOD0(Disconnect, void());
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

TEST_F(TransportTests, ConnectAndDisconnect)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Disconnect()).Times(1);
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    ASSERT_EQ(signalHandler.Messages.size(), 0);
    transport.Disconnect();
    ASSERT_EQ(signalHandler.Messages.size(), 0);
}

TEST_F(TransportTests, SendWithoutResponse)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST, {13}))).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Disconnect()).Times(1);
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    transport.Send(CreateMessage(MessageType::REQUEST, {13}));
    transport.Disconnect();
    ASSERT_EQ(signalHandler.Messages.size(), 0);
}

TEST_F(TransportTests, SendWithResponse)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST, {13})))
            .Times(1)
            .WillOnce(testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->ResponseReceived(CreateMessage(MessageType::RESPONSE, {19})); }));
    EXPECT_CALL(*_transportLowLevel.get(), Disconnect()).Times(1);
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    transport.Send(CreateMessage(MessageType::REQUEST, {13}));
    transport.Disconnect();
    ASSERT_EQ(signalHandler.Messages.size(), 1);
    ASSERT_EQ(signalHandler.Messages[0], CreateMessage(MessageType::RESPONSE, {19}));
}

TEST_F(TransportTests, SendWithResponseAndEvent)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST, {13})))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->ResponseReceived(CreateMessage(MessageType::RESPONSE, {19})); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->EventReceived(CreateMessage(MessageType::EVENT, {99})); })));
    EXPECT_CALL(*_transportLowLevel.get(), Disconnect()).Times(1);
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    transport.Send(CreateMessage(MessageType::REQUEST, {13}));
    transport.Disconnect();
    ASSERT_EQ(signalHandler.Messages.size(), 2);
    ASSERT_EQ(signalHandler.Messages[0], CreateMessage(MessageType::RESPONSE, {19}));
    ASSERT_EQ(signalHandler.Messages[1], CreateMessage(MessageType::EVENT, {99}));
}

TEST_F(TransportTests, SendWithResponseAndData)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST, {13})))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->ResponseReceived(CreateMessage(MessageType::RESPONSE, {19})); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateDataMessage(1, 0, {66})); })));
    EXPECT_CALL(*_transportLowLevel.get(), Disconnect()).Times(1);
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    transport.Send(CreateMessage(MessageType::REQUEST, {13}));
    transport.Disconnect();
    ASSERT_EQ(signalHandler.Messages.size(), 2);
    ASSERT_EQ(signalHandler.Messages[0], CreateMessage(MessageType::RESPONSE, {19}));
    ASSERT_EQ(signalHandler.Messages[1], CreateDataMessage(1, 0, {66}));
}

TEST_F(TransportTests, UnorderedData)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST, {13})))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->ResponseReceived(CreateMessage(MessageType::RESPONSE, {19})); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateDataMessage(2, 0, {67})); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateDataMessage(1, 0, {66})); })));
    EXPECT_CALL(*_transportLowLevel.get(), Disconnect()).Times(1);
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    transport.Send(CreateMessage(MessageType::REQUEST, {13}));
    transport.Disconnect();
    ASSERT_EQ(signalHandler.Messages.size(), 3);
    ASSERT_EQ(signalHandler.Messages[0], CreateMessage(MessageType::RESPONSE, {19}));
    ASSERT_EQ(signalHandler.Messages[1], CreateDataMessage(1, 0, {66}));
    ASSERT_EQ(signalHandler.Messages[2], CreateDataMessage(2, 0, {67}));
}

TEST_F(TransportTests, DelayedData)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST, {13})))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->ResponseReceived(CreateMessage(MessageType::RESPONSE, {19})); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateDataMessage(9, 0, {77})); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateDataMessage(1, 0, {66})); })));
    EXPECT_CALL(*_transportLowLevel.get(), Disconnect()).Times(1);
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    transport.Send(CreateMessage(MessageType::REQUEST, {13}));
    transport.Disconnect();
    ASSERT_EQ(signalHandler.Messages.size(), 2);
    ASSERT_EQ(signalHandler.Messages[0], CreateMessage(MessageType::RESPONSE, {19}));
    ASSERT_EQ(signalHandler.Messages[1], CreateDataMessage(1, 0, {66}));
}

TEST_F(TransportTests, DelayedDataGreaterMaxDelayedCount)
{
    EXPECT_CALL(*_transportLowLevel.get(), Connect()).Times(1);
    EXPECT_CALL(*_transportLowLevel.get(), Send(CreateMessage(MessageType::REQUEST, {13})))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->ResponseReceived(CreateMessage(MessageType::RESPONSE, {19})); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateDataMessage(9, 0, {99})); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateDataMessage(4, 0, {44})); }),
                                     testing::InvokeWithoutArgs([this](){ emit _transportLowLevel.get()->DataReceived(CreateDataMessage(3, 0, {33})); })));
    EXPECT_CALL(*_transportLowLevel.get(), Disconnect()).Times(1);
    Transport transport(_transportLowLevel.get(), _messageCheckStrategy.get());
    TransportSignalHandler signalHandler(&transport);
    transport.Connect();
    ASSERT_NO_THROW(transport.Send(CreateMessage(MessageType::REQUEST, {13})));
    ASSERT_TRUE(signalHandler.DataProcessFailed);
    ASSERT_EQ(signalHandler.Messages.size(), 1);
    ASSERT_EQ(signalHandler.Messages[0], CreateMessage(MessageType::RESPONSE, {19}));
    transport.Disconnect();
}

}
