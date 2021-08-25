#include "sum.h"

Sum::Sum(std::shared_ptr<Expression> one_,  std::shared_ptr<Expression> two_):
    one(one_),
    two(two_)
{

}

Sum::~Sum()
{
}

Money Sum::reduce(const Bank& bank, std::string currency) const
{
    int amount = one->reduce(bank, currency).amount() +
            two->reduce(bank, currency).amount();
    return Money(amount, currency);
}

std::shared_ptr<Expression> Sum::plus(std::shared_ptr<Expression> object)
{
    return std::static_pointer_cast<Expression>(
                std::make_shared<Sum>(shared_from_this(), object));
}

std::shared_ptr<Expression> Sum::multipliedBy(int multiplier) const
{
    return std::static_pointer_cast<Expression>(
                 std::make_shared<Sum>(one->multipliedBy(multiplier),
                                       two->multipliedBy(multiplier)));
}
