#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include "money.h"
#include "bank.h"
#include "sum.h"

class MoneyTest : public testing::Test
{
public:
    MoneyTest()
    {
    }

};



TEST_F(MoneyTest, testMultiplication)
{
    //EXPECT_EQ(*Money::dollar(10), *Money::dollar(5)->multipliedBy(2));
    //EXPECT_EQ(*Money::dollar(15), *Money::dollar(5)->multipliedBy(3));
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
   // EXPECT_EQ(*five, sum->one);
   // EXPECT_EQ(*five, sum->two);
}

TEST_F(MoneyTest, testReduceSum)
{
    auto d3 = Money::dollar(3);
    auto d4 = Money::dollar(4);
    Sum sum(d3.get(), d4.get());
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

TEST_F(MoneyTest, testReduceMoneyDifferentCurrency)
{
    Bank bank;
    bank.addRate("CHF", "USD", 2);
    Money result = bank.reduce(*Money::franc(2), "USD");
    EXPECT_EQ(*Money::dollar(1), result);
}

TEST_F(MoneyTest, testMixedAdditional)
{
    std::shared_ptr<Expression> fiveDollar = Money::dollar(5);
    std::shared_ptr<Expression> tenFrancs = Money::franc(10);
    Bank bank;
    bank.addRate("CHF", "USD", 2);
    Money result = bank.reduce(*fiveDollar->plus(*tenFrancs), "USD");
    EXPECT_EQ(Money::dollar(10)->amount(), result.amount());
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
