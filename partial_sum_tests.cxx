#include <algorithm>
#include <iostream>
#include <vector>

#include "partial_sum.hpp"

int main()
{
    std::vector<int> ints(10);
    std::vector<int> outs(10);
    std::generate(ints.begin(), ints.end(), [] {
        static int n{ 0 };
        return n++;
    });

    std::cout << "Ints:\n";
    for (auto& v : ints)
    {
        std::cout << v << " ";
    }

    sequential_partial_sum(ints.begin(), ints.end(), outs.begin());

    std::cout << "\n\n Out: \n";
    for (auto& v : outs)
    {
        std::cout << v << " ";
    }
    
    std::cin.get();
    return 0;
}