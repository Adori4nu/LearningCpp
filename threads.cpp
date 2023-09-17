// #pragma once
#include <iostream>
#include <thread>
#include "common.hpp"

void foo()
{
    std::cout << "Hello world! from foo. Thread id: " << std::this_thread::get_id() << std::endl;
}

void throwing_fun()
{
    std::cout << "This is log from throwing function." << std::endl;
    throw std::runtime_error("This is a runtime error.");
}

void run()
{
    std::thread foo_thread(foo);
    thread_guard tg(foo_thread);
    try {
        throwing_fun();
        foo_thread.join();
    } catch(...) {
        // foo_thread.join();
    }
}

class callable_class {
    public:
    void operator()()
    {
        std::cout << "Hello world! from class. Thread id: " << std::this_thread::get_id() << std::endl;
    }
};

int main()
{
    std::thread thread_1(foo);
    thread_1.join();

    callable_class obj;
    std::thread thread_2(obj);
    thread_2.join();

    std::thread thread_3([]
    {
        std::cout <<  "Hello world! from lambda. Thread id: " << std::this_thread::get_id() << std::endl;
    });
    thread_3.join();

    std::cout << "Hello world! from main. Thread id: " << std::this_thread::get_id() << std::endl;

    run();
}