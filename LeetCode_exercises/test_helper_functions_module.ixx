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