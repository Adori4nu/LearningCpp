#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

#pragma region spinlock class definition
class spinlock_mutex
{
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
    
public:
    spinlock_mutex()
    {}

    void lock()
    {
        while (flag.test_and_set(std::memory_order_acquire));
    }

    void unlock()
    {
        flag.clear(std::memory_order_release);
    }
};
#pragma endregion

spinlock_mutex mutex;

auto func() -> void
{
    std::lock_guard<spinlock_mutex> lg(mutex);
    std::cout << std::this_thread::get_id() << " Hello " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5'000));
}

auto run_code() -> void
{
    std::thread thread_1(func);
    std::thread thread_2(func);
    
    thread_1.join();
    thread_2.join();
}