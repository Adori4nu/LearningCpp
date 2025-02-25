#include <cassert>
#include <iostream>
#include <string>
#include <string_view>
#include <print>

import Graph;
import Test_helpers;

auto main() -> int
{
    std::cout << "\n\t\033[1;33m---Test of Graph---\033[0m\n";
    myjunk::Graph<std::string_view> empty_Graph;
    test_operation("empty_Graph", empty_Graph, [](auto& c){ c.addVertex("A"); });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ c.addVertex("B"); });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ c.addVertex("C"); });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ c.addVertex("D"); });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ c.addEdge("A", "B"); });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ c.addEdge("A", "C"); });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ c.addEdge("A", "D"); });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ c.addEdge("D", "B"); });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ c.addEdge("D", "C"); });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ std::cout << "\033[35mNumber of nodes: " << c.size() << "\033[0m\n"; });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ std::cout << "\033[1;32mRemove edges A-B test: " << std::boolalpha << c.removeEdge("A", "B") << "\033[0m\n"; });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ std::cout << "\033[35mNumber of nodes: " << c.size() << "\033[0m\n"; });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ std::cout << "\033[1;32mRemove vert \"D\" test: " << std::boolalpha << c.removeVertex("D") << "\033[0m\n"; });
    test_operation("empty_Graph", empty_Graph, [](auto& c){ std::cout << "\033[35mNumber of nodes: " << c.size() << "\033[0m\n"; });
    
    bool rem_res{ empty_Graph.removeVertex("B") };
    if (rem_res)
    std::print("\033[1;32mVertex B removed\033[0m\n");
    else
    std::print("\033[1;31mFailed Vertex B couldn't be removed\033[0m\n");
    rem_res = empty_Graph.removeVertex("B");
    if (rem_res)
    std::print("\033[1;32mVertex B removed\033[0m\n");
    else
    std::print("\033[1;31mFailed Vertex B couldn't be removed 2nd time\033[0m\n");
    test_operation("empty_Graph", empty_Graph, [](auto& c){ std::cout << "\033[35mNumber of nodes: " << c.size() << "\033[0m\n"; });
}