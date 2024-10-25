#include <algorithm>
#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "partial_sum.hpp"
// #include "utils.hpp"

const size_t testSize{ 10'000'000 };

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::milli;

void print_results(const char* const tag
    , high_resolution_clock::time_point startTime
    , high_resolution_clock::time_point endTime
)
{
    std::chrono::duration<double, std::milli> duration{endTime - startTime};
    
    std::cout << tag << ": Time: " << duration.count() << "ms" << std::endl;
}

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
    parallel_partial_sum(ints.begin(), ints.end());
    endTime = high_resolution_clock::now();
    print_results("parallel scan manual", startTime, endTime);

    std::cin.get();
    return 0;
}