module;

#include <iostream>
#include <string>

#include "test_helpers.h"

export module Test_helpers;

export template<typename Container, typename Func, typename... Args>
void test_operation(const std::string& name, Container& container, Func operation, Args&&... args) {
    operation(container, std::forward<Args>(args)...);
    std::cout << "Content of " << name << ":\n" << container << "\n";
}

// inline string captureOutput(function<void()> func) {
//     std::stringstream buffer;
//     std::streambuf* sbuf = std::cout.rdbuf();
//     cout.rdbuf(buffer.rdbuf());
//     func();
//     cout.rdbuf(sbuf);
//     return buffer.str();
// }

// {
//     cout << "\n----- Test: Single Node BST -----\n";
//     BinarySearchTree tree;
//     std::string output = captureOutput([&]() {
//         tree.insert(10);
//         tree.BFS();
//     });
//     cout << "EXPECTED: 10 \n";
//     cout << "RETURNED: " << output << "\n";
//     cout << (output == "10 " ? "PASS\n" : "FAIL\n");
// }