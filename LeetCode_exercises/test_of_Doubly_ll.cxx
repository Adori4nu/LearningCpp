#include <iostream>

import Doubly_LL;

#define TEST_OPERATION(container, operation, ...) \
    do { \
        container.operation(__VA_ARGS__); \
        std::cout << "Content of " << #container << ":\n" << container << "\n"; \
    } while (0);

template<typename Container, typename Func, typename... Args>
void test_operation(const std::string& name, Container& container, Func operation, Args&&... args) {
    operation(container, std::forward<Args>(args)...);
    std::cout << "Content of " << name << ":\n" << container << "\n";
}

auto main() -> int
{
    Doubly_LinkedList<int> empty_dll{};
    Doubly_LinkedList fu_bar_dll{69};

    std::cout << "Both Doubly Linked Lists crated!!!\n";
    std::cout << "DLL size: " << sizeof(empty_dll) << "\n";
    std::cout << "DLL length: " << std::size(empty_dll) << "\n";

    std::cout << "Content of empty_dll:\n" << empty_dll << "\n";
    std::cout << "Content of fu_bar_dll:\n" << fu_bar_dll << "\n";

    std::cout << "Append to empty_dll:\n";
    empty_dll.append(69);
    std::cout << "Content of empty_dll:\n" << empty_dll << "\n";
    empty_dll.append(42);
    std::cout << "Content of empty_dll:\n" << empty_dll << "\n";
    empty_dll.deleteLast();
    std::cout << "Content of empty_dll:\n" << empty_dll << "\n";
    empty_dll.deleteLast();
    std::cout << "Content of empty_dll:\n" << empty_dll << "\n";
    empty_dll.deleteLast();
    std::cout << "Content of empty_dll:\n" << empty_dll << "\n";

    test_operation("empty_dll", empty_dll, [](auto& c){ c.prepend(0); });
    test_operation("empty_dll", empty_dll, [](auto& c){ c.prepend(2); });
    test_operation("empty_dll", empty_dll, [](auto& c){ c.prepend(4); });
    TEST_OPERATION(empty_dll, prepend, 0);
    TEST_OPERATION(empty_dll, prepend, 2);
    TEST_OPERATION(empty_dll, Doubly_LinkedList::prepend, 4);

    for (int i{0}; i <= 7; ++i)
    {
        TEST_OPERATION(empty_dll, Doubly_LinkedList::deleteFirst);
    }
    
    test_operation("empty_dll", empty_dll, [](auto& c){ c.append(69); });
    test_operation("empty_dll", empty_dll, [](auto& c){ c.append(42); });
    test_operation("empty_dll", empty_dll, [](auto& c){ c.append(777); });

    std::cout << "Content of empty_ll at index[-1]: ";
    if (auto res{empty_dll.get(-1)})
        std::cout << *res << "\n";
    else
        std::cout << "Nullptr\n";
    std::cout << "Content of empty_ll at index[1]: ";
    if (auto res{empty_dll.get(1)})
        std::cout << *res << "\n";
    else
        std::cout << "Nullptr\n";
    std::cout << "Content of empty_ll at index[5]: ";
    if (auto res{empty_dll.get(5)})
        std::cout << *res << "\n";
    else
        std::cout << "Nullptr\n";
    std::cout << "Content of empty_ll at index[0]: ";
    if (auto res{empty_dll.get(0)})
        std::cout << *res << "\n";
    else
        std::cout << "Nullptr\n";
    
    TEST_OPERATION(empty_dll, Doubly_LinkedList::set, -1, 9);
    test_operation("empty_dll", empty_dll, [](auto& c) { c.set(1, 666); });
    test_operation("empty_dll", empty_dll, [](auto& c) { c.set(5, 666); });

    test_operation("fu_bar_dll", fu_bar_dll, [](auto& c) { c.insert(0, 304); });
    test_operation("fu_bar_dll", fu_bar_dll, [](auto& c) { c.insert(2, 2'137); });
    test_operation("fu_bar_dll", fu_bar_dll, [](auto& c) { c.insert(2, 666); });
    test_operation("fu_bar_dll", fu_bar_dll, [](auto& c) { c.insert(5, 911); });
    test_operation("fu_bar_dll", fu_bar_dll, [](auto& c) { c.deleteNode(1); });
    test_operation("fu_bar_dll", fu_bar_dll, [](auto& c) { c.deleteNode(0); });
    test_operation("fu_bar_dll", fu_bar_dll, [](auto& c) { c.deleteNode(1); });
}