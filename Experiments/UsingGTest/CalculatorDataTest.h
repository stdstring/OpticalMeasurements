#pragma once

#include <string>
#include <tuple>

#include "gtest/gtest.h"

#include "Calculator.h"

typedef std::tuple<int, int, int, int, std::string> CalculatorData;

class CalculatorDataTest : public testing::TestWithParam<CalculatorData>
{
};

TEST_P(CalculatorDataTest, CheckCalculator)
{
    CalculatorData data = GetParam();
    Calculator calculator;
    EXPECT_EQ(std::get<2>(data), calculator.Add(std::get<0>(data), std::get<1>(data)));
    EXPECT_EQ(std::get<3>(data), calculator.Sub(std::get<0>(data), std::get<1>(data)));
}

INSTANTIATE_TEST_CASE_P(CheckCalculatorInstance,
                        CalculatorDataTest,
                        testing::Values(std::make_tuple(1, 2, 3, -1, "test1"),
                                        std::make_tuple(4, 1, 5, 3, "test13"),
                                        std::make_tuple(6, 11, 17, -5, "test666")),
                        [](const testing::TestParamInfo<CalculatorData>& info){ return std::get<4>(info.param); });

