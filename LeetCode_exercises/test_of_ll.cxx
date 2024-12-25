#include <iostream>

import LinkedList;

auto main() -> int
{
    std::cout << "LeetCode exercises:\n--- test of LL ---\n1. Constructor" << std::endl;
    LinkedList<int> empty_ll{};
    LinkedList int_ll{42};
    
    std::cout << "Both Linked Lists crated!!!\n";
    std::cout << "Empty LL size: " << sizeof(empty_ll) << "\n";
    std::cout << "Int LL size: " << sizeof(int_ll) << "\n";
    std::cout << "Size of int: " << sizeof(int) << "\n";
    std::cout << "Size of pointer: " << sizeof(int*) << "\n";
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    std::cout << "Content of int_ll: " << int_ll << "\n";

    std::cout << "Append to empty_ll:\n";
    empty_ll.append(69);
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.append(42);
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.append(6);
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.append(9);
    std::cout << "Content of empty_ll: " << empty_ll << std::endl;

    std::cin.get();
    std::cin.get();
}