#include <gtest/gtest.h>
#include "../src/fib.h"

TEST(FibTest, BasicValues) {
    EXPECT_EQ(fib(0), 0);
    EXPECT_EQ(fib(1), 1);
    EXPECT_EQ(fib(10), 55);
}
