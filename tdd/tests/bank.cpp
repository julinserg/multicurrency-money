#include "bank.h"

Money Bank::reduce(const Expression& expression, std::string currency) const
{
    return expression.reduce(*this, currency);
}

void Bank::addRate(std::string from, std::string to, int rate)
{
    m_mapCurrencyRate[PairCurrency(from, to)] = rate;
}

int Bank::rate(std::string from, std::string to) const
{
    if(from == to)
        return 1;

    auto it = m_mapCurrencyRate.find(PairCurrency(from, to));
    if( it != m_mapCurrencyRate.end() )
       return it->second;
    else
        return 0;
}

bool operator == (const PairCurrency& object1, const PairCurrency& object2)
{
    return object1.equals(object2);
}

bool operator < (const PairCurrency& object1, const PairCurrency& object2)
{
    return object1.less(object2);
}
