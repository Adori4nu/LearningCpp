#pragma once
#include <string>

class Parser
{
public:
    Parser();
protected:
    static std::string parseExtracted(std::string extractedStr) noexcept;
public:
    static std::string parse() noexcept;
};