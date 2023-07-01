#include <iostream>
#include <vector>
#include <cmath>

int two_crystall_balls(std::vector<bool>& breaks)
{
    const int jump_ammount = std::floor(std::sqrt(breaks.size()));
    std::cout << "jump_ammount: " << jump_ammount << std::endl;

    int i = jump_ammount;
    for (; i < breaks.size(); i += jump_ammount)
    {
        if (breaks[i]) {
            std::cout << "i: " << i << std::endl;
            break;
        }
    }
    i -= jump_ammount;
    std::cout << "i: " << i << std::endl;
    // for (; i < breaks.size(); i++)
    // {
    //     if (breaks[i]) return i;
    // }
    for (int j = 0; j < jump_ammount && i < breaks.size(); ++j, ++i)
    {
        if (breaks[i]) {
            std::cout << "j: " << j << std::endl;
            return i;
        }
    }

    return -1;
}

int main()
{
    std::vector<bool> breaks;
    for (int i = 0; i < 50; i++)
    {
        i < 30 ? breaks.emplace_back(false) : breaks.emplace_back(true);
    }

    for (const auto& dest : breaks)
    {
        std::cout << "breaks: " << dest << std::endl;
    }
    std::cout << breaks.size() << std::endl;
    std::cout << two_crystall_balls(breaks) << std::endl;
}