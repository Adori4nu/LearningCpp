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
        Vector<int> v(n);
        {
            Vector<int> v2(n * 2);
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
    Vector<int> gv(10);
    Vector<int>* gp = new Vector<int>(100);
    fct(5);
    delete gp;
    // std::cout << "Sum of input: " << sum_of_vec << std::endl;
    std::cout << "Input vec<int> values: ";
    Vector<int> v = vec_utils::read<int>(std::cin); // something is crashing
    std::cout << "\nvec<int> values: ";
    for (size_t s{}; s < v.size(); ++s)
        std::cout << v[s] << "\t";

#endif
    std::cin.get();
    std::cin.get();
}