#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MoneyTest : public testing::Test
{
public:
    MoneyTest()
    {
    }

};

class Dollar
{
public:
    Dollar(int amount): m_amount(amount)
    {
    }

    void multipledBy(int multiplier)
    {
        m_amount = m_amount * multiplier;
    }
    int amount() const noexcept
    {
        return m_amount;
    }
private:
    int m_amount;

};

TEST_F(MoneyTest, testMultiplication)
{
    Dollar five(5);
    five.multipledBy(2);
    EXPECT_EQ(10, five.amount());
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
