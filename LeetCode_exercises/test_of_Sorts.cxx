#include <cassert>
#include <iostream>
#include <print>
#include "../Vector.hpp"

import Test_helpers;
import Sorts;

auto main() -> int
{
    Vector<int> my_vec{};
    my_vec.EmplaceBack(3);
    my_vec.EmplaceBack(6);
    my_vec.EmplaceBack(4);
    my_vec.EmplaceBack(2);
    my_vec.EmplaceBack(1);
    my_vec.EmplaceBack(5);

    std::println("\t\t\033[1;36m--- [Test of Sorts] ---\033[0m\n");
    std::println("\033[1;33m--- [Bubble sort] ---\033[0m");
    std::cout << "\033[34mBefore sorting:\033[0m ";
    for (const auto& val : my_vec)
    {
        std::cout << val << " ";
    }
    my_junk::bubble_sort(my_vec);
    std::cout << "\n\033[35mAfter sorting: \033[0m ";
    for (size_t i{0}; i < my_vec.Size(); ++i)
    {
        if (my_vec[i] == int(i) + 1)
            std::cout << "\033[32m"<< my_vec[i] << "\033[0m ";
        else if (my_vec[i] != int(i) + 1)
            std::cout << "\033[1;31m"<< my_vec[i] << "\033[0m ";
    }
    std::cout << "\n\n";

    std::println("\033[1;33m--- [Selection sort] ---\033[0m");
    my_vec[0] = 3;
    my_vec[1] = 6;
    my_vec[2] = 4;
    my_vec[3] = 2;
    my_vec[4] = 1;
    my_vec[5] = 5;
    std::cout << "\033[34mBefore sorting:\033[0m ";
    for (const auto& val : my_vec)
    {
        std::cout << val << " ";
    }
    my_junk::selection_sort(my_vec);
    std::cout << "\n\033[35mAfter sorting: \033[0m ";
    for (size_t i{0}; i < my_vec.Size(); ++i)
    {
        if (my_vec[i] == int(i) + 1)
            std::cout << "\033[32m"<< my_vec[i] << "\033[0m ";
        else if (my_vec[i] != int(i) + 1)
            std::cout << "\033[1;31m"<< my_vec[i] << "\033[0m ";
    }
    std::cout << "\n\n";

    std::println("\033[1;33m--- [Insertion sort] ---\033[0m");
    my_vec[0] = 3;
    my_vec[1] = 6;
    my_vec[2] = 4;
    my_vec[3] = 2;
    my_vec[4] = 1;
    my_vec[5] = 5;
    std::cout << "\033[34mBefore sorting:\033[0m ";
    for (const auto& val : my_vec)
    {
        std::cout << val << " ";
    }
    my_junk::insertion_sort(my_vec);
    std::cout << "\n\033[35mAfter sorting: \033[0m ";
    for (size_t i{0}; i < my_vec.Size(); ++i)
    {
        if (my_vec[i] == int(i) + 1)
            std::cout << "\033[32m"<< my_vec[i] << "\033[0m ";
        else if (my_vec[i] != int(i) + 1)
            std::cout << "\033[1;31m"<< my_vec[i] << "\033[0m ";
    }
    std::cout << "\n\n";

    std::println("\033[1;33m--- [Merge sort] ---\033[0m");
    my_vec[0] = 3;
    my_vec[1] = 6;
    my_vec[2] = 4;
    my_vec[3] = 2;
    my_vec[4] = 1;
    my_vec[5] = 5;
    my_vec.EmplaceBack(9);
    my_vec.EmplaceBack(8);
    my_vec.EmplaceBack(7);
    std::cout << "\033[34mBefore sorting:\033[0m ";
    for (const auto& val : my_vec)
    {
        std::cout << val << " ";
    }
    my_junk::merge_sort(my_vec);
    std::cout << "\n\033[35mAfter sorting: \033[0m ";
    for (size_t i{0}; i < my_vec.Size(); ++i)
    {
        if (my_vec[i] == int(i) + 1)
            std::cout << "\033[32m"<< my_vec[i] << "\033[0m ";
        else if (my_vec[i] != int(i) + 1)
            std::cout << "\033[1;31m"<< my_vec[i] << "\033[0m ";
    }
    std::cout << "\n\n";
}