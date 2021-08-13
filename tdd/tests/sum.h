#ifndef SUM_H
#define SUM_H

#include "expression.h"
#include "money.h"

class Sum : public Expression
{
public:
    Sum(const Money& one_, const Money& two_);

    Money reduce(const Bank& bank, std::string currency) const override;

    Money one;
    Money two;
};

#endif // SUM_H
