#include <atomic>
#include <assert.h>
#include <iostream>
#include <memory>
#include <thread>

std::atomic<int> data[5];
std::atomic<bool> sync1(false), sync2(false);
// t2 is in sync with t1 and t3 is in sync with t2
// so t3 is in sync with t1 via transitive relationship
auto thread_1_func() -> void
{
    data[0].store(42, std::memory_order_relaxed);
    data[1].store(45, std::memory_order_relaxed);
    data[2].store(47, std::memory_order_relaxed);
    data[3].store(49, std::memory_order_relaxed);
    data[4].store(56, std::memory_order_relaxed);
    sync1.store(true, std::memory_order_release);
}

auto thread_2_func() -> void
{
    while (!sync1.load(std::memory_order_acquire));
    sync2.store(true, std::memory_order_release);
}

auto thread_3_func() -> void
{
    while (!sync2.load(std::memory_order_acquire));
    assert(data[0].load(std::memory_order_relaxed) == 42);
    assert(data[1].load(std::memory_order_relaxed) == 45);
    assert(data[2].load(std::memory_order_relaxed) == 47);
    assert(data[3].load(std::memory_order_relaxed) == 49);
    assert(data[4].load(std::memory_order_relaxed) == 56);
}

auto run_code() -> void
{
    std::thread thread_1(thread_1_func);
    std::thread thread_2(thread_2_func);
    std::thread thread_3(thread_3_func);
}

int main()
{
    run_code();

    std::cin.get();
    return 0;
}