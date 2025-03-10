#include <iostream>
#include <string>
#include <format>
#include <print>
#include <vector>

static uint64_t counter_rec{0};
static uint64_t counter_btm_up{0};

// top down aproach recursive with memoization O(2n - 1)
auto fibonacci_rec(uint64_t n) -> uint64_t {
    ++counter_rec;
    static std::vector<uint64_t> memo(100, UINT64_MAX);
    if (memo[n] != UINT64_MAX) return memo[n];

    if (n == 0 || n == 1) return n;

    uint64_t fib1{ fibonacci_rec(n - 1) };
    uint64_t fib2{ fibonacci_rec(n - 2) };

    if (fib1 > std::numeric_limits<uint64_t>::max() - fib2) {
        throw std::overflow_error("Fibonacci result too large");
    }
    
    memo[n] = fib1 + fib2;
    return memo[n];
}

// dynamic bottom up aproach O(n - 1) no memo
auto fibonacci_btm_up(uint64_t n) -> uint64_t {
    std::vector<uint64_t> fib_list;
    fib_list.push_back(0);
    fib_list.push_back(1);

    for (size_t index{2}; index <= n; ++index) {
        ++counter_btm_up;
        if (fib_list[index - 1] > std::numeric_limits<uint64_t>::max() - fib_list[index - 2]) {
            throw std::overflow_error("Fibonacci result too large");
        }
        fib_list.push_back(fib_list[index - 1] + fib_list[index - 2]);
    }

    return fib_list.back();
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
        uint64_t n{ std::stoull(argv[1]) };

        if (n >= 94) {
            throw std::overflow_error("Input value too large - would cause overflow");
        }

        uint64_t result{ fibonacci_rec(n) };
        uint64_t result_btm_up{ fibonacci_btm_up(n) };

        std::println("Fibonacci sequence of {} is \033[1;32m{}\033[0m function call counter is \033[1;31m{}\033[0m (recursive with memo).", n, result, counter_rec);
        std::println("Fibonacci sequence of {} is \033[1;32m{}\033[0m function call counter is \033[1;31m{}\033[0m (bottom_up).", n, result_btm_up, counter_btm_up);
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