#include <iostream>
#include <string>

struct Entry{
    std::string name;
    int value;
};

auto read_entry(std::istream& is) -> Entry
{
    std::string s;
    int i;
    is >> s >> i;
    return {s, i};
}

int main()
{
    auto e{read_entry(std::cin)};
    std::cout << "{" << e.name << ", " << e.value << "}\n";

    auto [n, v]{read_entry(std::cin)};
    std::cout << "{" << n << ", " << v << "}\n";

    std::cin.get();
    std::cin.get();
}