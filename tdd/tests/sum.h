#ifndef SUM_H
#define SUM_H

#include "expression.h"
#include "money.h"

class Sum : public Expression, public std::enable_shared_from_this<Sum>
{
public:
    Sum(std::shared_ptr<Expression> one_, std::shared_ptr<Expression> two_);
    ~Sum();

    Money reduce(const Bank& bank, std::string currency) const override;
    std::shared_ptr<Expression> plus(std::shared_ptr<Expression> object) override;
    std::shared_ptr<Expression> multipliedBy(int multiplier) const override;

    std::shared_ptr<Expression> one;
    std::shared_ptr<Expression> two;
};

#endif // SUM_H
