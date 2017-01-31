#include "gtest/gtest.h"

#include "Calculator.h"

TEST(CalculatorTest, Add)
{
    Calculator calculator;
    ASSERT_EQ(3, calculator.Add(1, 2));
    ASSERT_EQ(5, calculator.Add(2, 3));
}

TEST(CalculatorTest, Sub)
{
    Calculator calculator;
    ASSERT_EQ(3, calculator.Sub(7, 4));
    ASSERT_EQ(-4, calculator.Sub(2, 6));
}
