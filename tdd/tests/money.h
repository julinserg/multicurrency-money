#ifndef MONEY_H
#define MONEY_H

#include "expression.h"


#include <memory>
#include <string>

class Money : public Expression
{
public:
    Money(int amount, std::string currency);

    bool equals(const Money& object) const noexcept;

    static std::shared_ptr<Money> dollar(int amount);

    static std::shared_ptr<Money> franc(int amount);

    std::shared_ptr<Money> multipliedBy(int multiplier);

    std::shared_ptr<Expression> plus(const Money& object);

    std::string currency() const noexcept;

    int amount() const noexcept;

    Money reduce(const Bank& bank, std::string currency) const override;


protected:
    const int m_amount;
    const std::string m_currency;
};

bool operator == (const Money& object1, const Money& object2);

#endif // MONEY_H
