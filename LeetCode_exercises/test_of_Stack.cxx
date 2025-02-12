#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

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

    std::string input = "Hello";
    std::string expected = "olleH";
    assert(reverseString(input) == expected);
    std::cout << "\n\033[32mTest off reversing string passed\033[0m\n\n";

    std::string empty = "";
    std::string equal = "(Hello)";
    std::string moreOpen = "(Noice()";
    std::string moreClosed = "(()->value))";
    assert(isBalancedParentheses(empty));
    assert(isBalancedParentheses(equal));
    assert(!isBalancedParentheses(moreOpen));
    assert(!isBalancedParentheses(moreClosed));
    std::cout << "\n\033[32mTest off parentheses ballanced passed\033[0m\n\n";

    Stack<int> s;
    s.push(5);
    s.push(2);
    s.push(7);
    s.push(1);
    s.push(3);

    std::cout << "\033[34mBefore sorting: " << s << "\033[0m\n";
    sortStack(s);
    std::cout << "After sorting: " << s;

    assert(s.top() == 1);
    s.pop();
    assert(s.top() == 2);
    s.pop();
    assert(s.top() == 3);
    s.pop();
    assert(s.top() == 5);
    s.pop();
    assert(s.top() == 7);
    s.pop();

    std::cout << "\n\033[32mTest off Stack sort int passed\033[0m\n\n";
}