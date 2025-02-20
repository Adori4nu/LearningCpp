#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

import Hash_Map;
import Test_helpers;
auto main() -> int
{
    NodeHashMap<int> empty_int_map;
    std::cout << empty_int_map << "\n";
    NodeHashMap<std::string> string_map{"Container Type", "unordered map"};
    std::cout << string_map << "\n";

}