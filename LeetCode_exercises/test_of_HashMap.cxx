#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

import Hash_Map;
import Test_helpers;

auto main() -> int
{
    NodeHashMap<int> empty_int_map;
    test_operation("empty_int_map", empty_int_map, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    NodeHashMap<std::string> string_map{"Container Type", "unordered map"};
    test_operation("string_map", string_map, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    test_operation("string_map", string_map, [](auto& c){ c.set("42", "foo_bar"); });
    test_operation("string_map", string_map, [](auto& c){ c.set("69", "noice"); });
    test_operation("string_map", string_map, [](auto& c){ c.set("777", "lucky_one"); });
    test_operation("string_map", string_map, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    if (auto res{ string_map.find("69") }; res && *res == "noice")
    std::cout << "\033[32m" << *res << "\033[0m\n";
    else
    std::cout << "\033[31mResult not found in unordered map\033[0m\n";
    if (auto res{ string_map.find("420") }; !res)
    std::cout << "\033[31mResult not found in unordered map\033[0m\n";
    
    test_operation("string_map", string_map, [](auto& c){ c.set("69", "Noice!!!"); });
    auto res{ string_map.keys() };
    for(auto key : res)
        std::cout <<  "\033[35mKey: " << key << "\033[0m\n";
}