#pragma once

#include <QList>
#include <QObject>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ComplexCalculator.h"
#include "ISimpleCalculator.h"

class SimpleCalculatorMock : public ISimpleCalculator
{
public:
    SimpleCalculatorMock(QObject *parent = 0) : ISimpleCalculator(parent) {}
    MOCK_METHOD2(Add, int(int left, int right));
    MOCK_METHOD2(Sub, int(int left, int right));
};

TEST(ComplexCalculatorTest, CalcA_Case1)
{
    testing::StrictMock<SimpleCalculatorMock> simpleCalculator;
    EXPECT_CALL(simpleCalculator, Add(3, 8))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([&simpleCalculator](){ emit simpleCalculator.OddResult(11); }), testing::Return(11)));
    EXPECT_CALL(simpleCalculator, Sub(8, 11))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([&simpleCalculator](){ emit simpleCalculator.OddResult(-3); }), testing::Return(-3)));
    EXPECT_CALL(simpleCalculator, Add(11, 3)).Times(1).WillOnce(testing::Return(14));
    EXPECT_CALL(simpleCalculator, Add(3, 2))
            .Times(1)
            .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([&simpleCalculator](){ emit simpleCalculator.OddResult(5); }), testing::Return(5)));
    ComplexCalculator complexCalculator(&simpleCalculator);
    ASSERT_EQ(27, complexCalculator.CalcA(3, 8, 11));
    ASSERT_EQ(QList<int>({11, -3, 5}), complexCalculator.OddResults);
}
