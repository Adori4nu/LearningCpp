#include <atomic>
#include <assert.h>
#include <iostream>
#include <memory>
#include <thread>

std::atomic<bool> atm_b1, atm_b2;
std::atomic<int> atm_int;

// this example may fail because there is a lack of synchronization
// between groups of threads A, C and B, D
auto write_atm_b1() -> void
{
    atm_b1.store(true, std::memory_order_release);
}

auto write_atm_b2() -> void
{
    atm_b2.store(true, std::memory_order_release);
}

auto read_b1_then_b2() -> void
{
    while (!atm_b1.load(std::memory_order_acquire)); // loop until x is true

    if (atm_b2.load(std::memory_order_acquire))
    {
        atm_int++;
    }
}

auto read_b2_then_b1() -> void
{
    while (!atm_b2.load(std::memory_order_acquire)); // loop until x is true

    if (atm_b1.load(std::memory_order_acquire))
    {
        atm_int++;
    }
}

auto run_code() -> void
{
    atm_b1 = false;
    atm_b2 = false;
    atm_int = 0;

    std::thread thread_a(write_atm_b1);
    std::thread thread_b(write_atm_b2);
    std::thread thread_c(read_b1_then_b2);
    std::thread thread_d(read_b2_then_b1);

    thread_a.join();
    thread_b.join();
    thread_c.join();
    thread_d.join();

    assert(atm_int != 0);
}

int main()
{
    run_code();

    std::cin.get();
    return 0;
}