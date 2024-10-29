#include <atomic>
#include <assert.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <thread>


std::atomic<int> count;
std::queue<int> data_queue;
int32_t max_count{ 20 };

auto writer_queue() -> void
{
    for (size_t i{ 0 }; i < 20; ++i)
    {
        data_queue.push(i);
    }

    count.store(20, std::memory_order_release);
}

auto reader_queue() -> void
{
    while (true)
    {
        int item_index{ 0 };
        if (!(item_index = count.fetch_sub(1, std::memory_order_acquire) <= 0))
        {
            // wait for items
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }
        // process the item
    }
}

auto run_code() -> void
{
    std::thread writer_thread(writer_queue);
    std::thread reader_thread1(reader_queue);
    std::thread reader_thread2(reader_queue);
}

int main()
{
    run_code();

    std::cin.get();
    return 0;
}