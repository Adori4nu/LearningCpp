#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<bool> data_ready{ false };
std::vector<int> data_vector;

// happend before
// synchronized with relation ship
auto reader_func() -> void
{
    while (!data_ready)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << data_vector[0] << std::endl;
}

// happend before
// inter thread hahappend before relationship - we pushed before setting the flag
// so other function in other thread was waiting for flag before getting the value
// we synchronized the data avoiding reading invariants in this simple way
auto writer_func() -> void
{
    data_vector.push_back(3);
    data_ready.store(true);
}

auto run_code() -> void
{
    std::thread reader_thread(reader_func);
    std::thread writer_thread(writer_func);

    reader_thread.join();
    writer_thread.join();
}

int main()
{
    run_code();

    std::cin.get();
    return 0;
}