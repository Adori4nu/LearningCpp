#include <iostream>
#include <mutex>
#include <list>
#include <thread>

std::list<int> my_list;
std::mutex mut;

void add_to_list(int const& x)
{
    mut.lock();
    my_list.push_front(x);
    mut.unlock();
}

void add_to_list_lg(int const& x)
{
    std::lock_guard<std::mutex> lg(mut);
    my_list.push_front(x);
}

void size()
{
    mut.lock();
    auto size{ my_list.size() };
    mut.unlock();
    std::cout << "list size is " << size << "." << std::endl;
}

void run_code()
{
    std::thread thread_1(add_to_list, 4);
    std::thread thread_2(add_to_list, 11);

    thread_1.join();
    thread_2.join();
}

int main()
{
    run_code();
}