#define VEC_IMP 45
#include <iostream>
#include <string>

#if VEC_IMP == 22 || VEC_IMP == 23
#include "Vector_imps.hpp"
#else
import Vector;
#endif

int main()
{
    double sum_of_vec{};

#if VEC_IMP == 22 || VEC_IMP == 23

    std::cout << "Podrozdział 2" << std::endl;
    read_and_sum(sum_of_vec, 3);
    std::cout << "Sum of input: " << sum_of_vec << std::endl;

#endif
#if VEC_IMP == 30

    std::cout << "Podrozdział 3" << std::endl;
    read_and_sum(sum_of_vec, 3);
    std::cout << "Sum of input: " << sum_of_vec << std::endl;

#endif
#if VEC_IMP == 40 || VEC_IMP == 45

    std::cout << "Podrozdział 4" << std::endl;
    read_and_sum(sum_of_vec, 3);
    std::cout << "Sum of input: " << sum_of_vec << std::endl;

#endif
    std::cin.get();
    std::cin.get();
}