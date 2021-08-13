#ifndef MONEY_H
#define MONEY_H

#include "expression.h"


#include <memory>
#include <string>

class Money : public Expression, public std::enable_shared_from_this<Money>
{
public:
    Money(int amount, std::string currency);
    ~Money();

    bool equals(const Money& object) const noexcept;

    static std::shared_ptr<Money> dollar(int amount);

    static std::shared_ptr<Money> franc(int amount);

    std::shared_ptr<Expression> multipliedBy(int multiplier) const override;

    std::shared_ptr<Expression> plus(std::shared_ptr<Expression> object);

    std::string currency() const noexcept;

    int amount() const noexcept;

    Money reduce(const Bank& bank, std::string currency) const override;


protected:
    const int m_amount;
    const std::string m_currency;
};

bool operator == (const Money& object1, const Money& object2);

#endif // MONEY_H
