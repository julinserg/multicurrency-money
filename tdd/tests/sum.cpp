#include "sum.h"

Sum::Sum(const Money& one_, const Money& two_):
    one(one_),
    two(two_)
{

}

Money Sum::reduce(const Bank& bank, std::string currency) const
{
    int amount = one.amount() + two.amount();
    return Money(amount, currency);
}
