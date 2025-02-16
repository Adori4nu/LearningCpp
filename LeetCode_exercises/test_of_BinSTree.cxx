#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

import Bin_Search_Tree;
import Test_helpers;

auto main() -> int
{
    TreeNodeBase<int> empty_int_tree;
    std::cout << empty_int_tree.m_root;
    TreeNodeBase int_tree{69};
    std::cout << "\n" << int_tree.m_root;
}