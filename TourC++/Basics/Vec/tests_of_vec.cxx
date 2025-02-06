#define VEC_IMP 52
#include <iostream>
#include <string>

#if VEC_IMP == 22 || VEC_IMP == 23
#include "Vector_imps.hpp"
#else
import Vector;
#endif

#if VEC_IMP == 52

    void fct(size_t n)
    {
        Vector v(n);
        {
            Vector v2(n * 2);
        }
    }

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
#if VEC_IMP == 52

    std::cout << "Podrozdział 5" << std::endl;
    Vector gv(10);
    std::cout << "Sum of input: " << sum_of_vec << std::endl;

#endif
    std::cin.get();
    std::cin.get();
}