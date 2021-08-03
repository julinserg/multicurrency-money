#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

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

    std::unique_ptr<Dollar> multipliedBy(int multiplier)
    {
        return std::make_unique<Dollar>(m_amount * multiplier);
    }

    bool equals(const Dollar& object)
    {
        return object.amount() == m_amount;
    }

    int amount() const noexcept
    {
        return m_amount;
    }
private:
    const int m_amount;

};

TEST_F(MoneyTest, testMultiplication)
{
    Dollar five(5);
    auto result2 = five.multipliedBy(2);
    EXPECT_EQ(10, result2->amount());
    auto result3 = five.multipliedBy(3);
    EXPECT_EQ(15, result3->amount());
}

TEST_F(MoneyTest, testEquality)
{
    Dollar five1(5);
    Dollar five2(5);
    Dollar six(6);
    EXPECT_EQ(five1.equals(five2), true);
    EXPECT_EQ(five1.equals(six), false);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
