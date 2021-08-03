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

class Money
{
public:
    Money(int amount): m_amount(amount)
    {
    }

    bool equals(const Money& object) const
    {
        return object.m_amount == m_amount;
    }

protected:
    const int m_amount;
};

class Dollar : public Money
{
public:
    Dollar(int amount): Money(amount)
    {
    }

    std::unique_ptr<Dollar> multipliedBy(int multiplier)
    {
        return std::make_unique<Dollar>(m_amount * multiplier);
    }

};

bool operator == (const Dollar& object1, const Dollar& object2)
{
    return object1.equals(object2);
}

class Franc : public Money
{
public:
    Franc(int amount): Money(amount)
    {
    }

    std::unique_ptr<Franc> multipliedBy(int multiplier)
    {
        return std::make_unique<Franc>(m_amount * multiplier);
    }
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
    EXPECT_EQ(Dollar(5).equals(Dollar(5)), true);
    EXPECT_EQ(Dollar(5).equals(Dollar(6)), false);

    EXPECT_EQ(Franc(5).equals(Franc(5)), true);
    EXPECT_EQ(Franc(5).equals(Franc(6)), false);
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
