#include <atomic>
#include <assert.h>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

struct X
{
    int i;
    std::string s;
};

std::atomic<X*> p;
std::atomic<int> a;

// consume only synchronizes the consumed value as
// a guarantee rest of the values may not be synced
auto create_x() -> void
{
    X* x = new X;
    x->i = 42;
    x->s = "Hello";

    a.store(20, std::memory_order_relaxed);
    p.store(x, std::memory_order_release);
}

auto use_x() -> void
{
    X* x;
    while (!(x = p.load(std::memory_order_consume)));
    assert(x->i == 42);
    assert(x->s == "Hello");
    assert(a.load(std::memory_order_relaxed) == 20);
}

auto run_code() -> void
{
    std::thread creation_thread(create_x);
    std::thread use_thread(use_x);

    creation_thread.join();
    use_thread.join();
}

int main()
{
    run_code();

    std::cin.get();
    return 0;
}