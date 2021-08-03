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

    bool equals(const Dollar& object) const
    {
        return object.m_amount == m_amount;
    }

private:
    const int m_amount;
};

bool operator == (const Dollar& object1, const Dollar& object2)
{
    return object1.equals(object2);
}

class Franc
{
public:
    Franc(int amount): m_amount(amount)
    {
    }

    std::unique_ptr<Franc> multipliedBy(int multiplier)
    {
        return std::make_unique<Franc>(m_amount * multiplier);
    }

    bool equals(const Franc& object) const
    {
        return object.m_amount == m_amount;
    }

private:
    const int m_amount;
};

bool operator == (const Franc& object1, const Franc& object2)
{
    return object1.equals(object2);
}

TEST_F(MoneyTest, testMultiplication)
{
    Dollar five(5);
    EXPECT_EQ(Dollar(10), *five.multipliedBy(2));
    EXPECT_EQ(Dollar(15), *five.multipliedBy(3));
}

TEST_F(MoneyTest, testEquality)
{
    Dollar five1(5);
    Dollar five2(5);
    Dollar six(6);
    EXPECT_EQ(five1.equals(five2), true);
    EXPECT_EQ(five1.equals(six), false);
}

TEST_F(MoneyTest, testFrancMultiplication)
{
    Franc five(5);
    EXPECT_EQ(Franc(10), *five.multipliedBy(2));
    EXPECT_EQ(Franc(15), *five.multipliedBy(3));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
