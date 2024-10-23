#include <algorithm>
#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::milli;
using std::random_device;
using std::sort;
using std::vector;

const size_t testSize{ 1'000'000 };
const int iterationCount{ 5 };

void print_result(const char* const tag
    , const vector<double>& sorted
    , high_resolution_clock::time_point startTime
    , high_resolution_clock::time_point endTime
)
{
    std::chrono::duration<double, std::milli> duration{endTime - startTime};
    
    std::cout << std::fixed << std::setprecision(2) << tag << ": Lowest number: " << sorted.front()
     << " Highest number: " << sorted.back()
      << " Time: " << duration.count() << "ms" << std::endl;
}

int main()
{
    random_device rd;

    std::cout << "Testing with " << testSize << " doubles...\n";
    vector<double> doubles(testSize);
    for (auto& d : doubles)
    {
        d = static_cast<double>(rd());
    }

    //how mutch time it takes to sort them without multi threading
    for (int i{ 0 }; i < iterationCount; ++i)
    {
        vector<double> sorted(doubles);
        const auto startTime{ high_resolution_clock::now() };
        std::sort(sorted.begin(), sorted.end());
        const auto endTime{ high_resolution_clock::now() };
        print_result("Serial STL", sorted, startTime, endTime);
    }

    for (int i{ 0 }; i < iterationCount; ++i)
    {
        vector<double> sorted(doubles);
        const auto startTime{ high_resolution_clock::now() };
        std::sort(std::execution::par, sorted.begin(), sorted.end());
        const auto endTime{ high_resolution_clock::now() };
        print_result("Parallel STL", sorted, startTime, endTime);
    }
    
    std::cin.get();
    return 0;
}