#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

import Bin_Search_Tree;
import Test_helpers;

auto main() -> int
{
    TreeNodeBase<int> empty_int_tree;
    std::cout << empty_int_tree << "\n";
    TreeNodeBase int_tree{69};
    std::cout << int_tree << "\n";

    TreeNodeBase<std::string> string_tree{"noice"};
    test_operation("string_tree", string_tree, [](auto& c){ c.insert("wow"); });
    test_operation("string_tree", string_tree, [](auto& c){ c.insert("LOL"); });
    test_operation("string_tree", string_tree, [](auto& c){ c.insert("aaa"); });
    test_operation("string_tree", string_tree, [](auto& c){ c.insert("boo!"); });
    std::cout << "\033[34m--- test ---\nString_tree contains: " << "boo!" << "\033[0m\n";
    std::cout << (string_tree.contains("boo!") ? "\033[1;32mTrue" : "\033[1;31mFalse") 
    << "\033[0m\n";
    std::cout << "\033[34m--- test ---\nString_tree contains: " << "Nananananananana Batman!" << "\033[0m\n";
    std::cout << (string_tree.contains("Nananananananana Batman!") ? "\033[1;32mTrue" : "\033[1;31mFalse") 
    << "\033[0m\n";
    TreeNodeBase<float> floating_tree;
    test_operation("floating_tree", floating_tree, [](auto& c){ c.insert(2.1f); });
    test_operation("floating_tree", floating_tree, [](auto& c){ c.insert(1.2f); });
    test_operation("floating_tree", floating_tree, [](auto& c){ c.insert(3.3f); });
    test_operation("floating_tree", floating_tree, [](auto& c){ c.insert(3.3f); });
}