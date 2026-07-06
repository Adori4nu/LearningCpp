#pragma once
#include "board.hpp"
#include "ship.hpp"

#include <vector>

class Player
{
    Board board{};

    Destroyer destroyer{};
    Cruiser cruiser{};
    Battleship battleship{};
};