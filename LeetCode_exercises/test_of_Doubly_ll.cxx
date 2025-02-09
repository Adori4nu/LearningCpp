#include <iostream>
#include <cassert>

import Doubly_LL;
import Test_helpers;

#define TEST_OPERATION(container, operation, ...) \
    do { \
        container.operation(__VA_ARGS__); \
        std::cout << "Content of " << #container << ":\n" << container << "\n"; \
    } while (0);

auto testSwapFirstLast() -> void {
    // Test empty and single node lists
    Doubly_LinkedList<int> emptyList;
    emptyList.swapFirstLast();
    assert(emptyList.size() == 0);

    Doubly_LinkedList<int> singleList(1);
    singleList.swapFirstLast();
    assert(singleList.size() == 1);
    assert(singleList.getHead() == 1);
    assert(singleList.getTail() == 1);

    // Test 2-node list
    Doubly_LinkedList<int> twoNodeList;
    twoNodeList.append(1);
    twoNodeList.append(2);
    twoNodeList.swapFirstLast();
    assert(twoNodeList.getHead() == 2);
    assert(twoNodeList.getTail() == 1);
    assert(twoNodeList.get(0)->next->prev == twoNodeList.get(0));
    assert(twoNodeList.get(1)->prev->next == twoNodeList.get(1));

    // Test longer list
    Doubly_LinkedList<int> longList;
    for(int i = 1; i <= 5; i++) {
        longList.append(i);
    }
    longList.swapFirstLast();
    assert(longList.getHead() == 5);
    assert(longList.getTail() == 1);
    assert(longList.get(0)->next->prev == longList.get(0));
    assert(longList.get(4)->prev->next == longList.get(4));
    
    std::cout << "All swap tests passed!\n";
}

auto testReverse() -> void {
    
    Doubly_LinkedList<int> emptyList;
    emptyList.reverse();
    assert(emptyList.size() == 0);

    emptyList.append(1);
    emptyList.reverse();
    assert(emptyList.size() == 1);
    assert(emptyList.getHead() == 1);
    assert(emptyList.getTail() == 1);

    emptyList.append(2);
    emptyList.reverse();
    assert(emptyList.size() == 2);
    assert(emptyList.getHead() == 2);
    assert(emptyList.getTail() == 1);

    Doubly_LinkedList<int> longList;
    for(int i = 1; i <= 5; i++) {
        longList.append(i);
    }
    std::cout << "Content of longList:\n" << longList << "\n";
    
    longList.reverse();
    assert(longList.getHead() == 5);
    assert(longList.getTail() == 1);
    assert(longList.get(0)->value == 5);
    assert(longList.get(1)->value == 4);
    assert(longList.get(2)->value == 3);
    assert(longList.get(3)->value == 2);
    assert(longList.get(4)->value == 1);

    std::cout << "Content of longList:\n" << longList << "\n";
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

    testSwapFirstLast();
    testReverse();
}