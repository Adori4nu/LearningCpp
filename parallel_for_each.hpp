#pragma once

#include <cstdint>
#include <future>
#include <thread>
#include <vector>

#include "common_objs.hpp"
// video 44 at 4:20
template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f)
{
    uint64_t const lenght(std::distance(first, last));

    if (!lenght)
    {
        return;
    }

    // Number of threads to use calculation

    uint64_t const min_per_thread{ 25 };
    uint64_t const max_threads{
        (lenght + min_per_thread - 1) / min_per_thread
    };

    uint64_t const hardware_threads{ std::thread::hardware_concurrency() };
    uint64_t const num_threads{ std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads) };
    uint64_t const block_size{ lenght / num_threads };

    // Declaration of needed data structures

    std::vector<std::future<void>> futures(num_threads - 1);
    std::vector<std::thread> threads(num_threads - 1);
    join_threads joiner(threads);

    Iterator block_start = first;
    for (uint64_t i{ 0 }; i <= (num_threads - 2); ++i)
    {
        Iterator block_end{ block_start };
        std::advance(block_end, block_size);

        std::packaged_task<void(void)> task
        (
            [=]()
            {
                std::for_each(block_start, block_end, f);
            }
        );

        futures[i] = task.get_future();
        threads[i] = std::thread(std::move(task));

        block_start = block_end;
    }

    std::for_each(block_start, last, f);

    for (uint64_t i{0}; i < (num_threads - 1); ++i)
        futures[i].get();
}