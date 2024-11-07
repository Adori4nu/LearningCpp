#define VEC_IMP 23
#include <iostream>
#include <string>

// #if VEC_IMP == 22
// #include "Vector_imps.hpp"
// #else
// import Vector;
// #endif
#include "Vector_imps.hpp"

int main()
{
#if VEC_IMP == 22 || 23

    double sum_of_vec{};
    read_and_sum(sum_of_vec, 3);
    std::cout << "Sum of input: " << sum_of_vec << std::endl;

#endif

    std::cin.get();
}