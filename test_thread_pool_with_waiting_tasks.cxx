#include <iostream>
#include <numeric>

#include "thread_pool_waiting_for_tasks.hpp"

template<typename Iterator, typename T>
struct accumulate_block
{
    T operator()(Iterator first, Iterator last)
    {
        T value{ std::accumulate(first, last, T())};
        std::cout << std::this_thread::get_id() << " - " << value << std::endl;
        return value;
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    int64_t const length{ std::distance(first, last) };
    thread_pool_waiting pool;

    if(!length)
        return init;
    
    uint64_t const min_per_thread{ 25 };
    uint64_t const max_threads{ (length + min_per_thread - 1) / min_per_thread };

    uint64_t const hardware_threads{ std::thread::hardware_concurrency() };

    uint64_t const num_threads{ std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads) };

    uint64_t const block_size{ length / num_threads };

    std::vector<std::future<T>> futures(num_threads - 1);

    Iterator block_start{ first };
    for (size_t i{ 0 }; i < (num_threads - 1); ++i)
    {
        Iterator block_end{ block_start };
        std::advance(block_end, block_size);
        futures[i] = pool.submit(std::bind(accumulate_block<Iterator, T>(), block_start, block_end));
        block_start = block_end;
    }
    T last_result = accumulate_block<int*, int>()(block_start, last);

    T result = init;
    for (size_t i{ 0 }; i < ( num_threads - 1 ); ++i)
    {
        result += futures[i].get();
    }
    result += last_result;
    return result;
}

int main()
{
	std::cout << "Simple thread pool with waiting \n";
	const int size = 1000;
	int* my_array = new int[size];

	srand(0);

	for (size_t i = 0; i < size; i++)
	{
		//my_array[i] = rand() % 10;
		my_array[i] = 1;
	}

	long result = parallel_accumulate<int*, int>(my_array, my_array + size, 0);
	std::cout << "final sum is  - " << result << std::endl;
    std::cin.get();
	return 0;
}