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
class Dollar;
class Franc;
class Money
{
public:
    Money(int amount, std::string currency): m_amount(amount),
        m_currency(currency)
    {
    }

    bool equals(const Money& object) const noexcept
    {
        return object.m_amount == this->m_amount &&
                object.currency() == this->currency();
    }

    static std::shared_ptr<Money> dollar(int amount)
    {
        return std::static_pointer_cast<Money>(std::make_shared<Dollar>(amount));
    }

    static std::shared_ptr<Money> franc(int amount)
    {
        return std::static_pointer_cast<Money>(std::make_shared<Franc>(amount));
    }

    std::shared_ptr<Money> multipliedBy(int multiplier)
    {
        return std::make_unique<Money>(m_amount * multiplier, m_currency);
    }

    std::string currency() const noexcept
    {
        return m_currency;
    }

protected:
    const int m_amount;
    const std::string m_currency;
};

bool operator == (const Money& object1, const Money& object2)
{
    return object1.equals(object2);
}

class Dollar : public Money
{
public:
    Dollar(int amount): Money(amount, "USD")
    {
    }
};

class Franc : public Money
{
public:
    Franc(int amount): Money(amount, "CHF")
    {
    }
};


TEST_F(MoneyTest, testMultiplication)
{ 
    EXPECT_EQ(*Money::dollar(10), *Money::dollar(5)->multipliedBy(2));
    EXPECT_EQ(*Money::dollar(15), *Money::dollar(5)->multipliedBy(3));
}

TEST_F(MoneyTest, testEquality)
{
    EXPECT_EQ(Money::dollar(5)->equals(*Money::dollar(5)), true);
    EXPECT_EQ(Money::dollar(5)->equals(*Money::dollar(6)), false);

    EXPECT_EQ(Money::franc(5)->equals(*Money::franc(5)), true);
    EXPECT_EQ(Money::franc(5)->equals(*Money::franc(6)), false);

    EXPECT_EQ(Money::franc(5)->equals(*Money::dollar(5)), false);
}

TEST_F(MoneyTest, testFrancMultiplication)
{
    EXPECT_EQ(*Money::franc(10), *Money::franc(5)->multipliedBy(2));
    EXPECT_EQ(*Money::franc(15), *Money::franc(5)->multipliedBy(3));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
