#pragma once
#include <atomic>
#include <cstdint>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <list>
#include <thread>
#include <type_traits>
#include <vector>

// #include "common.hpp"
#include "common_objs.hpp"

#include "thread_safe_queue_wp.hpp"

#pragma region work stealing queue
class work_stealing_queue
{
    typedef function_wrapper data_type;
    std::deque<data_type> the_queue;
    mutable std::mutex the_mutex;

public:
    work_stealing_queue(){}

    work_stealing_queue(const work_stealing_queue&) = delete;
    work_stealing_queue& operator=(const work_stealing_queue&) = delete;

    void push(data_type data)
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        the_queue.push_front(std::move(data));
    }

    bool try_pop(data_type& res)
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        if (the_queue.empty())
        {
            return false;
        }

        res = std::move(the_queue.front());
        the_queue.pop_front();
        return true;
    }

    bool try_steal(data_type& res)
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        if (the_queue.empty())
        {
            return false;
        }

        res = std::move(the_queue.back());
        the_queue.pop_back();
        return true;
    }
};
#pragma endregion

#pragma region stealing work thread pool implementation
class thread_pool_stealing
{
    typedef function_wrapper task_type;

    std::atomic_bool done;
    thread_safe_queue<task_type> global_work_queue;
    std::vector<std::unique_ptr<work_stealing_queue>> queues;
    std::vector<std::thread> threads;
    join_threads joiner;

    static thread_local work_stealing_queue* local_work_queue;
    static thread_local unsigned my_index;

    void worker_thread(unsigned my_index_)
    {
        my_index = my_index_;
        local_work_queue = queues[my_index].get();
        while (!done)
        {
            run_pending_task();
        }
    }

    bool pop_task_from_local_queue(task_type& task)
    {
        return local_work_queue && local_work_queue->try_pop(task);
    }

    bool pop_task_from_pool_queue(task_type& task)
    {
        return global_work_queue.try_pop(task);
    }

    bool pop_task_from_other_thread_queue(task_type& task)
    {
        for (unsigned i{ 0 }; i < queues.size(); ++i)
        {
            unsigned const index{ (my_index + i + 1) % queues.size() };
            if (queues[index]->try_steal(task))
            {
                return true;
            }
        }

        return false;
    }
    
public:
    thread_pool_stealing() : done(false), joiner(threads)
    {    
        uint64_t const thread_count{ std::thread::hardware_concurrency() };
        try
        {
            for (size_t i{ 0 }; i < thread_count; ++i)
            {
                queues.push_back(std::unique_ptr<work_stealing_queue>(new work_stealing_queue));
                threads.push_back(std::thread(&thread_pool_stealing::worker_thread, this, i));
            }    
        }
        catch(...)
        {
            done = true;
            throw;
        }
    }

    ~thread_pool_stealing()
    {
        done = true;
    }

    template<typename Function_type>
    std::future<typename std::result_of<Function_type()>::type> submit(Function_type f)
    {
        typedef typename std::result_of<Function_type()>::type result_type;

        std::packaged_task<result_type()> task(std::move(f));
        std::future<result_type> res(task.get_future());
        
        if (local_work_queue)
        {
            local_work_queue->push(std::move(task));
        }
        else
        {
            global_work_queue.push(std::move(task));
        }
        return res;
    }

    void run_pending_task()
    {
        task_type task;
        if (pop_task_from_local_queue(task) || 
            pop_task_from_pool_queue(task) ||
            pop_task_from_other_thread_queue(task))
        {
            task();
        }
        else
        {
            std::this_thread::yield();
        }
    }
};
#pragma endregion

thread_local work_stealing_queue* thread_pool_stealing::local_work_queue;
thread_local unsigned thread_pool_stealing::my_index;

template<typename T>
struct sorter
{
    thread_pool_stealing pool;

    std::list<T> do_sort(std::list<T>& chunk_data)
    {
        if ( chunk_data.size() < 2)
        {
            return chunk_data;
        }

        std::list<T> result;
        result.splice(result.begin(), chunk_data, chunk_data.begin());
        T const& partition_val{ *result.begin() };

        typename std::list<T>::iterator divide_point{ std::partition(chunk_data.begin(),
            chunk_data.end(), [&](T const& val)
            {
                return val < partition_val; 
            }
        )};

        std::list<T> new_lower_chunk;
        new_lower_chunk.splice(new_lower_chunk.end(), chunk_data, chunk_data.begin()
            , divide_point
        );

        std::future<std::list<T>> new_lower{ pool.submit(std::bind(&sorter::do_sort
            , this, std::move(new_lower_chunk))) };

        std::list<T> new_higher(do_sort(chunk_data));

        result.splice(result.end(), new_higher);

        while (!new_lower._Is_ready())
        {
            pool.run_penging_task();
        }

        result.splice(result.begin(), new_lower.get());
        
        return result;
    }
};

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
    if (input.empty())
    {
        return input;
    }

    sorter<T> s;
    return s.do_sort(input);
}