#include <gtest/gtest.h>

int Add(int a,int b)
{
    return a+b;
}


TEST(AddFunctionTest, HandlesPositiveNumbers) {
    EXPECT_EQ(Add(1, 2), 3);
    EXPECT_EQ(Add(10, 15), 25);
}

TEST(AddFunctionTest, HandlesNegativeNumbers) {
    EXPECT_EQ(Add(-1, -2), -3);
    EXPECT_EQ(Add(-10, -15), -25);
}

TEST(AddFunctionTest, HandlesMixedNumbers) { 
    EXPECT_EQ(Add(-1, 1), 0);
    EXPECT_EQ(Add(-5, 5), 0);
}

TEST(AddFunctionTest, HandlesError) { 
    ASSERT_EQ(Add(1,1),0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
