#include "money.h"

#include "bank.h"
#include "sum.h"

Money::Money(int amount, std::string currency): m_amount(amount),
    m_currency(std::move(currency))
{
}

bool Money::equals(const Money& object) const noexcept
{
    return object.m_amount == this->m_amount &&
            object.currency() == this->currency();
}

std::shared_ptr<Money> Money::dollar(int amount)
{
    return std::make_shared<Money>(amount, "USD");
}

std::shared_ptr<Money> Money::franc(int amount)
{
    return std::make_shared<Money>(amount, "CHF");
}

std::shared_ptr<Money> Money::multipliedBy(int multiplier)
{
    return std::make_shared<Money>(m_amount * multiplier, m_currency);
}

std::shared_ptr<Expression> Money::plus(const Money& object)
{
    return std::static_pointer_cast<Expression>(
                std::make_shared<Sum>(*this, object));
}

std::string Money::currency() const noexcept
{
    return m_currency;
}

int Money::amount() const noexcept
{
    return m_amount;
}

Money Money::reduce(const Bank& bank, std::string currency) const
{
    int rate = bank.rate(m_currency, currency);

    return Money(m_amount/rate, currency);
}

bool operator == (const Money& object1, const Money& object2)
{
    return object1.equals(object2);
}
