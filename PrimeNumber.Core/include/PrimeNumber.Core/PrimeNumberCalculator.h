#pragma once

#include <PrimeNumber.Core/PrimeNumber.Core.API.h>
#include <string>
#include <vector>

template<typename TValue>
class PRIMENUMBERCORE_API PrimeNumberCalculator
{
public:

    PrimeNumberCalculator() = default;

    std::vector<TValue> GetPrimeNumbers(size_t i_till_value)
    {
        std::vector<TValue> V;
        bool prime = true;
        for (int i = 2; i <= i_till_value; i++)
        {
            prime = true;
            for (int j = 2; j <= i / 2; j++)
            {
                if (i % j == 0)
                {
                    prime = false;
                    break;
                }
            }

            if (prime)
            {
                if constexpr (std::is_same_v<std::string, TValue>)
                    V.emplace_back(std::to_string(i));

                else if constexpr (std::is_same_v<std::wstring, TValue>)
                    V.emplace_back(std::to_wstring(i));

                else
                    V.push_back(i);
            }

        }

        return V;
    }
};


