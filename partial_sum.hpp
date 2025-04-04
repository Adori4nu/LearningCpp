#pragma once
#include <cstdint>
#include <future>
#include <numeric>

#include "common_objs.hpp"

template<typename Iterator, typename OutIterator>
void sequential_partial_sum(Iterator first, Iterator last, OutIterator y)
{
    int64_t const lenght{ std::distance(first, last) };

    y[0] = first[0];

    for (size_t i{ 1 }; i < lenght; ++i)
    {
        y[i] = first[i] + y[i - 1];
    }
}

template<typename Iterator>
void parallel_partial_sum(Iterator first, Iterator last)
{
    typedef typename Iterator::value_type value_type;

    struct process_chunk
    {
        void operator()(Iterator begin
            , Iterator last
            , std::future<value_type>* previous_end_value
            , std::promise<value_type>* end_value
        )
        {
            try
            {
                Iterator end{ last };
                ++end;
                std::partial_sum(begin, end, begin);
                if (previous_end_value)
                {
                    //this is not first thread
                    auto addend{ previous_end_value->get() };
                    *last += addend;
                    if (end_value)
                    {
                        //not the last block
                        end_value->set_value(*last);
                    }
                    std::for_each(begin, last, [addend](value_type& item)
                        {
                            item += addend;    
                        });
                }
                else if (end_value)
                {
                    //this is the first thread
                    end_value->set_value(*last);
                }
            }
            catch(...)
            {
                if (end_value)
                {
                    end_value->set_exception(std::current_exception());
                }
                else
                {
                    //final block - main thread is the one process the final block
                    throw;
                }
            }
            
        }
    };

    int64_t const length{ std::distance(first, last) };
    if(!length)
        return;

    uint64_t const min_per_thread{ 25 };
    uint64_t const max_threads{ (length + min_per_thread - 1) / min_per_thread };
    uint64_t const hardware_threads = std::thread::hardware_concurrency();
    uint64_t const num_threads{ std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads) };
    uint64_t const block_size{ length / num_threads };


    std::vector<std::thread> threads(num_threads - 1);
    std::vector<std::promise<value_type>> end_values(num_threads - 1);
    std::vector<std::future<value_type>> previous_end_values;
    previous_end_values.reserve(num_threads - 1);

    join_threads joiner(threads);

    Iterator block_start{ first };
    for (int64_t i{ 0 }; i < (num_threads - 1); ++i)
    {
        Iterator block_last{ block_start };
        std::advance(block_last, block_size - 1);

        threads[i] = std::thread(
            process_chunk()
            , block_start
            , block_last
            , (i != 0) ? &previous_end_values[i - 1] : 0
            , &end_values[i]
        );

        block_start = block_last;
        ++block_start;
        previous_end_values.push_back(end_values[i].get_future());
    }

    Iterator final_element{ block_start };
    std::advance(final_element, std::distance(block_start, last) - 1);
    process_chunk()(block_start, final_element
        , (num_threads > 1) ? &previous_end_values.back() : 0, 0
    );
}