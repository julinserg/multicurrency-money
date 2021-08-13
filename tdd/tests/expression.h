#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

class Money;
class Bank;

class Expression
{
public:
    virtual Money reduce(const Bank& bank, std::string currency) const = 0;
};

#endif // EXPRESSION_H
