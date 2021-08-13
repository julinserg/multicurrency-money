#include "sum.h"

Sum::Sum(const Expression* one_,  const Expression* two_):
    one(one_),
    two(two_)
{

}

Money Sum::reduce(const Bank& bank, std::string currency) const
{
    int amount = one->reduce(bank, currency).amount() +
            two->reduce(bank, currency).amount();
    return Money(amount, currency);
}

std::shared_ptr<Expression> Sum::plus(const Expression& object)
{
    return nullptr;
}
