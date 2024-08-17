#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>
#include <chrono>
#include <mutex>

void print_result(std::shared_future<int>& fut)
{
    if (fut.valid())
    {
        std::cout << "Future is valid\n";
        std::cout << "value: " << fut.get() << '\n';
    }
    else
    {
        std::cout << "Future is invalid\n";
    }
}

void run_code()
{
    std::promise<int> prom;
    std::shared_future<int> fut(prom.get_future());

    std::thread th1(print_result, std::ref(fut));
    std::thread th2(print_result, std::ref(fut));

    prom.set_value(5);

    th1.join();
    th2.join();
}

int main()
{
    run_code();
    std::cin.get();
    return 0;
}