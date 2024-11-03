#include <atomic>
#include <cstdint>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

// #include "common.hpp"
#include "common_objs.hpp"

#include "thread_safe_queue.hpp"

#pragma region simple thread pool implementation
class thread_pool
{
    std::atomic_bool done;
    thread_safe_queue<std::function<void()>> work_queue;
    std::vector<std::thread> threads;
    join_threads joiner;

    void worker_thread()
    {
        while (!done)
        {
            std::function<void()> task;
            // if (work_queue.try_pop(task))
            if (work_queue.wait_pop(task))
            {
                task();
            }
            else
            {
                std::this_thread::yield();
            }
        }
    }
    
public:
    thread_pool() : done(false), joiner(threads)
    {    
        uint64_t const thread_count{ std::thread::hardware_concurrency() };
        try
        {
            for (size_t i{ 0 }; i < thread_count; ++i)
            {
                threads.push_back(std::thread(&thread_pool::worker_thread, this));
            }    
        }
        catch(...)
        {
            done = true;
            throw;
        }
    }

    ~thread_pool()
    {
        done = true;
    }

    template<typename function_type>
    void submit(function_type f)
    {
        work_queue.push(std::function<void()>(f));
    }
};
#pragma endregion