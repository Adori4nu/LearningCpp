#include <iostream>
#include <string>

import Stack;
import Test_helpers;

auto main() -> int
{
    Stack<int> empty_stack;
    Stack not_a_stack{ 6.9 };
    Stack<std::string, VectorBase> vector_stack{"wow"};

    std::cout << "Both Stacks crated!!!\n";
    test_operation("empty_stack", empty_stack, [](auto& c){ std::cout << "Height: " << c.size() << "\n"; });
    test_operation("not_a_stack", not_a_stack, [](auto& c){ std::cout << "Size of Stack: " << sizeof(c) << "\n"; });
    test_operation("vector_stack", vector_stack, [](auto& c){ c.push("noice"); });
}