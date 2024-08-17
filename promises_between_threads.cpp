#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>

void print_int(std::future<int>& fut)
{
    std::cout << "waiting for value from print thread \n";
    std::cout << "value: " << fut.get() << '\n';
}

void run_code()
{
    std::promise<int> prom;
    std::future<int> fut(prom.get_future());

    std::thread print_thread(print_int, std::ref(fut));

    std::this_thread::sleep_for(std::chrono::milliseconds(5'000));
    std::cout << "setting the value in main thread \n";
    prom.set_value(10);

    print_thread.join();
}

int main()
{
    run_code();
    std::cin.get();
}