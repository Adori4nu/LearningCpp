#include <atomic>
#include <assert.h>
#include <iostream>
#include <memory>
#include <thread>

std::atomic<bool> atm_b1, atm_b2;
std::atomic<int> atm_int;

auto write_atm_b1_then_atm_b2() -> void
{
    atm_b1.store(true, std::memory_order_relaxed);
    atm_b2.store(true, std::memory_order_release);

    std::cout << "Writer thread: Atomic bool 1: " << atm_b1.load(std::memory_order_relaxed) << std::endl;
    std::cout << "Writer thread: Atomic bool 2: " << atm_b2.load(std::memory_order_relaxed) << std::endl;
}

auto read_b2_then_b1() -> void
{
    while (!atm_b2.load(std::memory_order_acquire)); // loop until x is true

    std::cout << "Reader thread: Atomic bool 2: " << atm_b2.load(std::memory_order_relaxed) << std::endl;
    if (atm_b1.load(std::memory_order_relaxed))
    {
        atm_int++;
    }
    std::cout << "Reader thread: Atomic bool 1: " << atm_b1.load(std::memory_order_relaxed) << std::endl;
}

auto run_code() -> void
{
    atm_b1 = false;
    atm_b2 = false;
    atm_int = 0;

    std::thread writer_thread(write_atm_b1_then_atm_b2);
    std::thread reader_thread(read_b2_then_b1);

    writer_thread.join();
    reader_thread.join();

    assert(atm_int != 0);
}

int main()
{
    run_code();

    std::cin.get();
    return 0;
}