#ifndef SUM_H
#define SUM_H

#include "expression.h"
#include "money.h"

class Sum : public Expression
{
public:
    Sum(const Expression* one_, const Expression* two_);

    Money reduce(const Bank& bank, std::string currency) const override;
    std::shared_ptr<Expression> plus(const Expression& object) override;

    const Expression* one;
    const Expression* two;
};

#endif // SUM_H
