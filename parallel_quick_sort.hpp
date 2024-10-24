#pragma once

#include <algorithm>
#include <future>
#include <iostream>
#include <list>

template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input)
{
    //select the pivot value
    if (input.size() < 2)
    {
        return input;
    }
    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T pivot(*result.begin());

    //arrange the input array
    auto divide_point = std::partition(input.begin(), input.end()
    , [&](T const& t)
    {
        return t < pivot;
    });

    //call the sequential_quick_sort recursively
    std::list<T> lower_list;
    lower_list.splice(lower_list.end(), input, input.begin(), divide_point);

    auto new_lower(sequential_quick_sort(std::move(lower_list)));
    auto new_upper(sequential_quick_sort(std::move(input)));

    //arrange the result list
    result.splice(result.begin(), new_lower);
    result.splice(result.end(), new_upper);

    return result;
}

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
    //select the pivot value
    if (input.size() < 2)
    {
        return input;
    }
    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T pivot(*result.begin());

    //arrange the input array
    auto divide_point = std::partition(input.begin(), input.end()
    , [&](T const& t)
    {
        return t < pivot;
    });

    //call the sequential_quick_sort recursively
    std::list<T> lower_list;
    lower_list.splice(lower_list.end(), input, input.begin(), divide_point);

    auto new_lower(sequential_quick_sort(std::move(lower_list)));
    std::future<std::list<T>> new_upper_future
        (std::async(&parallel_quick_sort<T>, std::move(input)));

    //arrange the result list
    result.splice(result.begin(), new_lower);
    result.splice(result.end(), new_upper_future.get());

    return result;
}