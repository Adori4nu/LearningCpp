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
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.removeLast();
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.removeLast();
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.removeLast();
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.removeLast();
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.removeLast();
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.prepend(69);
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.prepend(42);
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.prepend(6);
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.prepend(9);
    std::cout << "Content of empty_ll: " << empty_ll << "\n";

    std::cout << "Content of empty_ll at index[-1]: ";
    if (auto res{empty_ll.get(-1)})
        std::cout << *res << "\n";
    else
        std::cout << "Nullptr\n";
    std::cout << "Content of empty_ll at index[0]: " << empty_ll.get(0) << "\n";
    std::cout << "Content of empty_ll at index[0]: ";
    if (auto res{empty_ll.get(0)})
        std::cout << *res << "\n";
    else
        std::cout << "Nullptr\n";
    std::cout << "Content of empty_ll at index[1]: " << empty_ll.get(1) << "\n";
    std::cout << "Content of empty_ll at index[2]: " << empty_ll.get(2)->value << "\n";
    std::cout << "Content of empty_ll at index[3]: " << empty_ll.get(3) << "\n";
    std::cout << "Content of empty_ll at index[3]: ";
    if (auto res{empty_ll.get(3)})
        std::cout << *res << "\n";
    else
        std::cout << "Nullptr\n";
    std::cout << "Content of empty_ll at index[4]: ";
    if (auto res{empty_ll.get(4)})
        std::cout << *res << "\n";
    else
        std::cout << "Nullptr\n";
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.deleteFirst();
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.deleteFirst();
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.deleteFirst();
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.deleteFirst();
    std::cout << "Content of empty_ll: " << empty_ll << "\n";
    empty_ll.deleteFirst();
    std::cout << "Content of empty_ll: " << empty_ll << std::endl;
    
    
    std::cin.get();
    std::cin.get();
}