#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

import Set;
import Test_helpers;

auto main() -> int
{
    std::cout << "\n\t\033[1;33m---Test of Set---\033[0m\n";
    myjunk::NodeSet<std::string_view> empty_Set;
    test_operation("empty_Set", empty_Set, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    myjunk::NodeSet<std::string_view> empty_Set2;
    empty_Set2.insert("5");
    empty_Set2.insert("6");
    empty_Set2.insert("9");
    empty_Set2.insert("9");
    empty_Set2.insert("77");
    test_operation("empty_Set2", empty_Set2, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    empty_Set2.insert("1");
    empty_Set2.insert("2");
    empty_Set2.insert("3");
    empty_Set2.insert("4");
    empty_Set2.insert("13");
    empty_Set2.insert("11");
    empty_Set2.insert("15");
    empty_Set2.insert("17");
    empty_Set2.insert("21");
    empty_Set2.insert("23");
    test_operation("empty_Set2", empty_Set2, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    empty_Set = std::move(empty_Set2);
    test_operation("empty_Set", empty_Set, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    test_operation("empty_Set2", empty_Set2, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
}