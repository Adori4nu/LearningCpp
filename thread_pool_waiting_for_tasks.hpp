#pragma once
#include <atomic>
#include <cstdint>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <type_traits>
#include <vector>

// #include "common.hpp"
#include "common_objs.hpp"

#include "thread_safe_queue_wp.hpp"

#pragma region waiting thread pool implementation
class thread_pool
{
    std::atomic_bool done;
    thread_safe_queue<function_wrapper> work_queue;
    std::vector<std::thread> threads;
    join_threads joiner;

    void worker_thread()
    {
        while (!done)
        {
            function_wrapper task;
            if (work_queue.try_pop(task))
            // if (work_queue.wait_pop(task))
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

    template<typename Function_type>
    std::future<typename std::result_of<Function_type()>::type> submit(Function_type f)
    {
        typedef typename std::result_of<Function_type()>::type result_type;
        std::packaged_task<result_type()> task(std::move(f));
        std::future<result_type> res(task.get_future());
        work_queue.push(std::move(task));
        return res;
    }
};
#pragma endregion