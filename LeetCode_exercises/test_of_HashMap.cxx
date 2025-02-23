#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

import Hash_Map;
import Test_helpers;

auto main() -> int
{
    std::cout << "\n\t\033[1;33m---Test of unordered (Multi) map---\033[0m\n";
    myjunk::NodeMultiMap<int> empty_int_Multimap;
    test_operation("empty_int_Multimap", empty_int_Multimap, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    myjunk::NodeMultiMap<std::string> string_Multimap{"Container Type", "unordered multi map"};
    test_operation("string_Multimap", string_Multimap, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    test_operation("string_Multimap", string_Multimap, [](auto& c){ c.set("42", "foo_bar"); });
    test_operation("string_Multimap", string_Multimap, [](auto& c){ c.set("69", "noice"); });
    test_operation("string_Multimap", string_Multimap, [](auto& c){ c.set("777", "lucky_one"); });
    test_operation("string_Multimap", string_Multimap, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    test_operation("string_Multimap", string_Multimap, [](auto& c){ c.set("69", "Noice!!!"); });
    auto multimap_res{ string_Multimap.keys() };
    for(auto key : multimap_res)
        std::cout <<  "\033[35mKey: " << key << "\033[0m\n";
    
    if (auto results{ string_Multimap.find("69") }; !results.empty()) {
        for (const auto& res : results) {
            if (res == "noice")
            std::cout << "\033[1;32m" << res << "\033[1;0m\n";
            else std::cout << "\033[34m" << res << "\033[0m\n";
        }
    }
    else
    std::cout << "\033[31mResult for 69 not found in unordered multi map\033[0m\n";

    if (auto res{ string_Multimap.find("420") }; res.empty()) {
        std::cout << "\033[31mResult for 420 not found in unordered multi map\033[0m\n";
    }

    std::cout << "\n\t\033[1;33m---Test of unordered map---\033[0m\n";

    myjunk::NodeMap<int> empty_int_map;
    test_operation("empty_int_map", empty_int_map, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    myjunk::NodeMap<std::string> string_map{"Container Type", "unordered map"};
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