#define COMPLEX_IMP 52
#include <iostream>

import Complex;

#if COMPLEX_IMP == 52
    void f(complex z)
    {
        complex a {2,3};
        complex b {1 / a};
        complex c {a+z*complex{1,2.3}};

        if (c != b)
            c = -(b / a) + 2 * b;
    }

#endif

int main()
{
#if COMPLEX_IMP == 52
    std::cout << "Podrozdział 5" << std::endl;
    complex comp{ 6, 9};
    f();
    std::cout << "funkcja wykonana" << std::endl;

#endif
    std::cin.get();
    std::cin.get();
}