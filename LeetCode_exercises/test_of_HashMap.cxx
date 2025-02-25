#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

import Hash_Map;
import Test_helpers;

auto main() -> int
{
    std::cout << "\n\t\033[1;33m---Test of unordered (Multi) map---\033[0m\n";
    myjunk::NodeMultiMap<std::string_view, int> empty_int_Multimap;
    test_operation("empty_int_Multimap", empty_int_Multimap, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    myjunk::NodeMultiMap<std::string_view, std::string> string_Multimap{"Container Type", "unordered multi map"};
    test_operation("string_Multimap", string_Multimap, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    test_operation("string_Multimap", string_Multimap, [](auto& c){ c.insert("42", "foo_bar"); });
    test_operation("string_Multimap", string_Multimap, [](auto& c){ c.insert("69", "noice"); });
    test_operation("string_Multimap", string_Multimap, [](auto& c){ c.insert("777", "lucky_one"); });
    test_operation("string_Multimap", string_Multimap, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    test_operation("string_Multimap", string_Multimap, [](auto& c){ c.insert("69", "Noice!!!"); });
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

    myjunk::NodeMap<std::string_view, int> empty_int_map;
    empty_int_map.insert("git", 42);
    test_operation("empty_int_map", empty_int_map, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    myjunk::NodeMap<int, int> int_map{ 42, 69 };
    int_map.insert(1, 111);
    int_map.insert(2, 111);
    int_map.insert(43, 111);
    test_operation("int_map", int_map, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
   
    myjunk::NodeMap<float, float> float_map{ 4.2f, 6.9f };
    float_map.insert(4.2f, 6.9f);
    float_map.insert(4.3f, 6.9f);
    float_map.insert(5.f, 6.9f);
    float_map.insert(2000.f, 6.9f);
    float_map.insert(2000.2f, 6.9f);
    test_operation("float_map", float_map, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    myjunk::NodeMap<double, std::string> d_s_map{ 42., "69" };
    d_s_map.insert(1.1, "lol");
    d_s_map.insert(1.11, "a");
    d_s_map.insert(111.11, "b");
    d_s_map.insert(1111.11, "asd");
    d_s_map.insert(123.11, "qwe");
    d_s_map.insert(118.11, "zxc");
    d_s_map.insert(2.011, "bbb");
    test_operation("d_s_map", d_s_map, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    myjunk::NodeMap<std::string_view, std::string> string_map{"Container Type", "unordered map"};
    test_operation("string_map", string_map, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    test_operation("string_map", string_map, [](auto& c){ c.insert("42", "foo_bar"); });
    test_operation("string_map", string_map, [](auto& c){ c.insert("69", "noice"); });
    test_operation("string_map", string_map, [](auto& c){ c.insert("777", "lucky_one"); });
    test_operation("string_map", string_map, [](auto& c){ std::cout << "\033[35mSize: " << c.size() << "\033[0m\n"; });
    
    if (auto res{ string_map.find("69") }; res && *res == "noice")
    std::cout << "\033[32m" << *res << "\033[0m\n";
    else
    std::cout << "\033[31mResult not found in unordered map\033[0m\n";
    if (auto res{ string_map.find("420") }; !res)
    std::cout << "\033[31mResult not found in unordered map\033[0m\n";
    
    test_operation("string_map", string_map, [](auto& c){ c.insert("69", "Noice!!!"); });
    auto res{ string_map.keys() };
    for(auto key : res)
        std::cout <<  "\033[35mKey: " << key << "\033[0m\n";
}