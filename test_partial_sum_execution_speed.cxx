#include <algorithm>
#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "partial_sum.hpp"
#include "utils.hpp"

const size_t testSize{ 10'000'000 };

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::milli;


int main()
{
    std::vector<int> ints(testSize, 1);
    std::vector<int> outs(testSize);


    auto startTime{ high_resolution_clock::now() };
    std::inclusive_scan(ints.cbegin(), ints.cend(), outs.begin());
    auto endTime{ high_resolution_clock::now() };
    print_results("sequential scan", startTime, endTime);

    startTime = high_resolution_clock::now();
    std::inclusive_scan(std::execution::par, ints.cbegin(), ints.cend(), outs.begin());
    endTime = high_resolution_clock::now();
    print_results("parallel scan", startTime, endTime);

    startTime = high_resolution_clock::now();
    parallel_partial_sum(ints.cbegin(), ints.cend());
    endTime = high_resolution_clock::now();
    print_results("parallel scan manual", startTime, endTime);
}