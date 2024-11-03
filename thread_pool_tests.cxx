#include "simple_thread_pool_intro.hpp"

int main()
{
    thread_pool pool;
    std::cout << "Testing thread pool" << std::endl;

    for (size_t i{ 0 }; i < 100; ++i)
    {
        pool.submit([=]{
            std::cout << i << ". Printed by thread - " << std::this_thread::get_id() << std::endl;
        });
    }

    std::cin.get();
    return 0;
}