#ifndef BANK_H
#define BANK_H

#include "money.h"

#include <map>

class PairCurrency
{
public:
    PairCurrency(std::string from_, std::string to_):
        m_from(from_), m_to(to_)
    {

    }

    bool equals(const PairCurrency& object) const
    {
        return m_from == object.m_from && m_to == object.m_to;
    }

    bool less(const PairCurrency& object) const
    {
        return m_from == object.m_from ? m_to < object.m_to : m_from < object.m_from;
    }


private:
    std::string m_from;
    std::string m_to;
};

bool operator == (const PairCurrency& object1, const PairCurrency& object2);
bool operator < (const PairCurrency& object1, const PairCurrency& object2);

class Bank
{
public:
    Money reduce(const Expression& expression, std::string currency) const;
    void addRate(std::string from, std::string to, int rate);
    int rate(std::string from, std::string to) const;

private:
    std::map<PairCurrency, int> m_mapCurrencyRate;
};

#endif // BANK_H
