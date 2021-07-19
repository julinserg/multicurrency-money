#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MoneyTest : public testing::Test
{
public:
    MoneyTest()
    {
    }

};

TEST_F(MoneyTest, testMoney)
{
    EXPECT_EQ(1+1, 2);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
