#include "gtest/gtest.h"

#include "AsyncCalculator.h"

TEST(AsyncCalculatorTest, Calculate)
{
    AsyncCalculatorRunner runner(300);
    AsyncCalulatorResultChecker::Check(&runner, 1, 2, 3);
    AsyncCalulatorResultChecker::Check(&runner, 2, 2, 3);
    AsyncCalulatorResultChecker::Check(&runner, 2, 2, 4);
}
