#include <iostream>
#include <string>
#include <format>
#include <print>

auto factorial(int n) -> uint64_t {
    if (n <= 1) return 1;

    uint64_t prev_factorial = factorial(n - 1);
    
    if (n > 0 && prev_factorial > std::numeric_limits<uint64_t>::max() / n) {
        throw std::overflow_error("Factorial result too large");
    }
    
    return n * prev_factorial;
}

auto main(int argc, char* argv[]) -> int
{
    if (argc != 2) 
    {
        std::cerr << std::format("\033[1;36mUsage: {} <positive_integer>\033[0m\n", argv[0]);
        return 1;
    }

    try 
    {
        int n{ std::stoi(argv[1]) };

        if (n < 0) {
            std::cerr << "\033[1;31mError: Please enter a non-negative integer.\033[0m\n";
            return 1;
        }

        uint64_t result{ factorial(n) };

        if (result == 0 && n > 1) {
            throw std::overflow_error("Factorial result too large");
        }

        std::println("Factorial of {} is \033[1;32m{}\033[0m", n, result);
    } 
    catch (const std::invalid_argument&) {
        std::cerr << "\033[1;31mError: Invalid input. Please enter a valid integer.\033[0m\n";
        return 1;
    }
    catch (const std::out_of_range&) {
        std::cerr << "\033[1;31mError: Number out of range. Please enter a smaller integer.\033[0m\n";
        return 1;
    }
    catch (const std::overflow_error&) {
        std::cerr << "\033[1;31mError: Overflow occurred. Result too large to represent.\033[0m\n";
        return 1;
    }

    return 0;
}