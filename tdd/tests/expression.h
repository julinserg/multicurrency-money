#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <memory>

class Money;
class Bank;

class Expression
{
public:
    virtual Money reduce(const Bank& bank, std::string currency) const = 0;
    virtual std::shared_ptr<Expression> plus(const Expression& object) = 0;
};

#endif // EXPRESSION_H
