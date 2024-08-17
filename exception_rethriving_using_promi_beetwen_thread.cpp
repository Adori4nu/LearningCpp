#include <cmath>
#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>

void throw_exception()
{
    throw std::invalid_argument("input canno't be negative!");
}

void calculate_square_root(std::promise<int>& prom)
{
    int x{ 1 };
    std::cout << "Please, enter an integer value: ";
    try
    {
        std::cin >> x;
        if (x < 0)
        {
            throw_exception();
        }
        prom.set_value(std::sqrt(x));
    }
    catch(const std::exception& e)
    {
        prom.set_exception(std::current_exception());
    } 
}

void print_result(std::future<int>& fut)
{
    try
    {
        int x{ fut.get() };
        std::cout << "value: " << x << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << "[exception caught: " << e.what() << "]\n";
    }
    
}

void run_code()
{
    std::promise<int> prom;
    std::future<int> fut(prom.get_future());

    std::thread printing_thread(print_result, std::ref(fut));
    std::thread calculation_thrad(calculate_square_root, std::ref(prom));

    printing_thread.join();
    calculation_thrad.join();
}

int main()
{
    run_code();
    std::cin.get();
}