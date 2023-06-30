#pragma once
#include "entity.hpp"

class PlayerVirtual : public EntityVirtual
{
private:
    std::string m_Name;
public:
    PlayerVirtual(const std::string& name)
        : m_Name(name) {}

    std::string GetName() override { return m_Name; };
};

class PlayerClass : public EntityClass
{
public:
    const char* Name;

    void PrintName()
    {
        std::cout << Name << std::endl;
    }
};