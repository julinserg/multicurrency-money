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

class Sum;
class Money;
class Expression
{
public:
    virtual Money reduce(std::string currency) const = 0;
};

class Money : public Expression
{
public:
    Money(int amount, std::string currency): m_amount(amount),
        m_currency(std::move(currency))
    {
    }

    bool equals(const Money& object) const noexcept
    {
        return object.m_amount == this->m_amount &&
                object.currency() == this->currency();
    }

    static std::shared_ptr<Money> dollar(int amount)
    {
        return std::make_shared<Money>(amount, "USD");
    }

    static std::shared_ptr<Money> franc(int amount)
    {
        return std::make_shared<Money>(amount, "CHF");
    }

    std::shared_ptr<Money> multipliedBy(int multiplier)
    {
        return std::make_shared<Money>(m_amount * multiplier, m_currency);
    }

    std::shared_ptr<Expression> plus(const Money& object)
    {
        return std::static_pointer_cast<Expression>(
                    std::make_shared<Sum>(*this, object));
    }

    std::string currency() const noexcept
    {
        return m_currency;
    }

    int amount() const noexcept
    {
        return m_amount;
    }

    Money reduce(std::string currency) const override
    {
        return *this;
    }


protected:
    const int m_amount;
    const std::string m_currency;
};

bool operator == (const Money& object1, const Money& object2)
{
    return object1.equals(object2);
}


class Sum : public Expression
{
public:
    Sum(const Money& one_, const Money& two_):
        one(one_),
        two(two_)
    {

    }

    Money reduce(std::string currency) const override
    {
        int amount = one.amount() + two.amount();
        return Money(amount, currency);
    }

    Money one;
    Money two;
};

class Bank
{
public:
    Money reduce(const Expression& expression, std::string currency) const
    {
        return expression.reduce(currency);
    }
};

TEST_F(MoneyTest, testMultiplication)
{
    EXPECT_EQ(*Money::dollar(10), *Money::dollar(5)->multipliedBy(2));
    EXPECT_EQ(*Money::dollar(15), *Money::dollar(5)->multipliedBy(3));
}

TEST_F(MoneyTest, testSimpleAddition)
{
    std::shared_ptr<Money> five = Money::dollar(5);
    std::shared_ptr<Expression> sum = five->plus(*five);
    Bank bank;
    Money reduced = bank.reduce(*sum, "USD");
    EXPECT_EQ(*Money::dollar(10), reduced);
}

TEST_F(MoneyTest, testPlusReturnsSum)
{
    std::shared_ptr<Money> five = Money::dollar(5);
    std::shared_ptr<Expression> result = five->plus(*five);
    std::shared_ptr<Sum> sum = std::static_pointer_cast<Sum>(result);
    EXPECT_EQ(*five, sum->one);
    EXPECT_EQ(*five, sum->two);
}

TEST_F(MoneyTest, testReduceSum)
{
    Sum sum(*Money::dollar(3), *Money::dollar(4));
    Bank bank;
    Money result = bank.reduce(sum, "USD");
    EXPECT_EQ(*Money::dollar(7), result);
}

TEST_F(MoneyTest, testReduceMoney)
{
     Bank bank;
     Money result = bank.reduce(*Money::dollar(1), "USD");
     EXPECT_EQ(*Money::dollar(1), result);
}


TEST_F(MoneyTest, testEquality)
{
    EXPECT_EQ(Money::dollar(5)->equals(*Money::dollar(5)), true);
    EXPECT_EQ(Money::dollar(5)->equals(*Money::dollar(6)), false);

    EXPECT_EQ(Money::franc(5)->equals(*Money::franc(5)), true);
    EXPECT_EQ(Money::franc(5)->equals(*Money::franc(6)), false);

    EXPECT_EQ(Money::franc(5)->equals(*Money::dollar(5)), false);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
