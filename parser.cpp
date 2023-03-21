#include "parser.hpp"

std::string Parser::parseExtracted(std::string extractedStr) noexcept
{
    return extractedStr;
}

std::string Parser::parse() noexcept
{
    std::string str = " Debug";
    return Parser::parseExtracted(str);
}