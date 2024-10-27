#include <atomic>
#include <iostream>
#include <thread>

void run_code()
{
    // std::atomic_flag flag1 = true;
    std::atomic_flag flag2 = ATOMIC_FLAG_INIT;

    std::cout << "1. previous flag value: " << flag2.test_and_set() << std::endl;
    std::cout << "2. previous flag value: " << flag2.test_and_set() << std::endl;

    flag2.clear();
    std::cout << "3. previous flag value: " << flag2.test_and_set() << std::endl;
}

int main()
{
    run_code();

    std::cin.get();
    return 0;
}