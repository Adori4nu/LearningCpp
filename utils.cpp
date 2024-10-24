#include "utils.hpp"
#include "common_objs.hpp"

#include <iostream>

void print_results(const char* const tag
    , high_resolution_clock::time_point startTime
    , high_resolution_clock::time_point endTime
)
{
    std::chrono::duration<double, std::milli> duration{endTime - startTime};
    
    std::cout << tag << ": Time: " << duration.count() << "ms" << std::endl;
}