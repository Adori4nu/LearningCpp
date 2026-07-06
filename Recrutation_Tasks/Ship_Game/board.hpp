#pragma once
#include "ship.hpp"
#include <array>
#include <cstddef>

struct Cell
{
    bool occupied { false };
    Ship* ship { nullptr };
    size_t sectionIndex { 0 };
};

class Board
{
    std::array<Cell, 100> grid{};

public:


};