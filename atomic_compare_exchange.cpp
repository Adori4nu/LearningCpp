#include <atomic>
#include <iostream>
#include <thread>

void run_code()
{
    std::atomic<int> x(20);

    int expected_value = 20; // if you change it to other than x compare exchange will show false "no"
    // and if expected value will be different than atomic int it will be exchanged to value of atomic
    // it means the int expected will be 20
    std::cout << "previous expected_value - " << expected_value << std::endl;
    bool return_val{ x.compare_exchange_weak(expected_value, 6) };
    
    std::cout << "operation successful    - " << (return_val ? "yes" : "no") << std::endl;
    std::cout << "current expected_value  - " << expected_value << std::endl;
    std::cout << "current x               - " << x.load() << std::endl;
}

int main()
{
    run_code();

    std::cin.get();
    return 0;
}