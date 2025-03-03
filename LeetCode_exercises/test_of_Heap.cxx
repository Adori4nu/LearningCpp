#include <cassert>
#include <iostream>
#include <string>

import Heap;
import Test_helpers;

auto main() -> int
{
    std::cout << "\n\t\033[1;33m---Test of Max Heap---\033[0m\n";
    my_junk::Heap<int> empty_heap;
    test_operation("empty_heap", empty_heap, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    empty_heap.insert(42);
    empty_heap.insert(777);
    empty_heap.insert(6);
    empty_heap.insert(9);
    empty_heap.insert(69);
    test_operation("empty_heap", empty_heap, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    my_junk::Heap<std::string> string_heap;
    test_operation("string_heap", string_heap, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    string_heap.insert("brain root");
    test_operation("string_heap", string_heap, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    string_heap.insert("max heap");
    string_heap.insert("no cap");
    string_heap.insert("foo");
    string_heap.insert("bar");
    string_heap.insert("Noice");
    test_operation("string_heap", string_heap, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
}