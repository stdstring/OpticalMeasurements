#include "gtest/gtest.h"

#include "CalculatorTest.h"
#include "CalculatorDataTest.h"
#include "ComplexCalculatorTest.h"

int main(int argc, char *argv[])
{
    //testing::GTEST_FLAG(throw_on_failure) = true;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
