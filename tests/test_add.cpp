#include "core/add.h"
#include <gtest/gtest.h>

TEST(AddTest, BasicCases) {
    EXPECT_EQ(add(1, 1), 2);
    EXPECT_EQ(add(-1, 1), 0);
    EXPECT_EQ(add(0, 0), 0);
    EXPECT_EQ(add(-5, -7), -12);
}
