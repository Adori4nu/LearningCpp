#include "entity.hpp"

class PlayerClass : public EntityClass
{
public:
    const char* Name;

    void PrintName()
    {
        std::cout << Name << std::endl;
    }
};