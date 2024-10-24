#pragma once

#include <atomic>
#include <cstdint>
#include <future>
#include <thread>
#include <vector>

#include "common_objs.hpp"

template<typename Iterator, typename MatchType>
Iterator parallel_find_pt(Iterator first, Iterator last, MatchType match)
{
    struct find_element
    {
        void operator()(Iterator begin, Iterator end
            , MatchType match
            , std::promise<Iterator>* result
            , std::atomic_bool* done_flag
            )
        {
            try
            {
                for(; (begin != end) && !std::atomic_load(done_flag); ++begin)
                {
                    if(*begin == match)
                    {
                        result->set_value(begin);
                        //done_flag.store(true);
                        std::atomic_store(done_flag, true);
                        return;
                    }
                }
            }
            catch(...)
            {
                result->set_exception(std::current_exception());
                done_flag->store(true);
            }
            
        }
    }

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

    std::promise<Iterator> result;
    std::atomic_bool done_flag(false);

    std::vector<std::thread> threads(num_threads - 1);
    {
        join_threads joiner(threads);

        Iterator block_start{ first };
        for (size_t i{ 0 }; i < (num_threads - 1); ++i)
        {
            Iterator block_end{ block_start };
            std::advance(block_end, block_size);
 
            threads[i] = std::thread(find_element(), block_start, block_end, match, &result, &done_flag);

            block_start = block_end;
        }

        find_element()(block_start, last, match, &result, &done_flag);
    }

    if (!done_flag.load())
    {
        return last;
    }
    
    return result.get_future().get();
}

template<typename Iterator, typename MatchType>
Iterator parallel_find_async(Iterator first, Iterator last, MatchType match, std::atomic<bool>* done_flag)
{
    try
    {
        uint64_t const length{ std::distance(first, last) };
        uint64_t const min_per_thread{ 25 };

        if (length < 2 * min_per_thread)
        {
            for (; (first != last) && done_flag; ++first)
            {
                if (*first == match)
                {
                    *done_flag = true;
                    return first;
                }
            }
            return last;
        }
        else
        {
            Iterator const mid_point{ first + length / 2 };
            std::future<Iterator> async_result{
                std::async(&parallel_find_async<Iterator, MatchType>, mid_point, last, match, std::ref(done_flag))
            };

            Iterator const direct_result{
                parallel_find_async(first, mid_point, match, done_flag);
            };

            return (direct_result == mid_point) ? async_result.get() : direct_result;
        }
    }
    catch(const std::exception& e)
    {
        *done_flag = true;
        std::cerr << e.what() << '\n';
        throw;
    }
    
}