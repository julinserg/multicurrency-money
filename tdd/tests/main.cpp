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
    Money(int amount): m_amount(amount)
    {
    }

    bool equals(const Money& object) const noexcept
    {
        return object.m_amount == this->m_amount && object.id() == this->id();
    }

    static std::shared_ptr<Money> dollar(int amount)
    {
        return std::static_pointer_cast<Money>(std::make_shared<Dollar>(amount));
    }

    static std::shared_ptr<Money> franc(int amount)
    {
        return std::static_pointer_cast<Money>(std::make_shared<Franc>(amount));
    }

    virtual std::shared_ptr<Money> multipliedBy(int multiplier) = 0;
    virtual int id() const noexcept = 0;

protected:
    const int m_amount;
};

bool operator == (const Money& object1, const Money& object2)
{
    return object1.equals(object2);
}

class Dollar : public Money
{
public:
    Dollar(int amount): Money(amount)
    {
    }

    std::shared_ptr<Money> multipliedBy(int multiplier) override
    {
        return std::make_unique<Dollar>(m_amount * multiplier);
    }   

    int id() const noexcept override
    {
        return 1;
    }

};

class Franc : public Money
{
public:
    Franc(int amount): Money(amount)
    {
    }

    std::shared_ptr<Money> multipliedBy(int multiplier) override
    {
        return std::make_unique<Franc>(m_amount * multiplier);
    }

    int id() const noexcept override
    {
        return 2;
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
