#include <atomic>
#include <iostream>
#include <thread>

void run_code()
{
    std::atomic<bool> flag_1; //on msvc it's constructed with false value by default
    std::cout << "flag 1 = " << flag_1 << std::endl;

    ////atomic types are nor copy constructable nor copy assignable (those are deleted functions)
    // std::atomic_bool flag_2(flag_1); //typedef on template type
    // std::atomic<bool> flag_3 = flag1;

    bool non_atomic_bool{true};
    std::atomic<bool> flag_4(non_atomic_bool);
    std::cout << "flag 4 = " << flag_4 << std::endl;

    std::atomic<bool> flag_5 = non_atomic_bool;
    std::cout << "flag 5 = " << flag_5 << std::endl;
}

void further_explanation()
{
    std::atomic<bool> x(false);
    std::cout << "atomic boolean is implemented lock free - "
         << (x.is_lock_free() ? "yes" : "no") << std::endl;

    std::atomic<bool> y(true);

    //store operations
    x.store(false);
    x.store(y);

    //load operations
    std::cout << "value of the atomic bool y - " << y.load() << std::endl;

    //exchange operations
    bool z = x.exchange(false);

    std::cout << "current value of atomic bool x - " << x.load() << std::endl;
    std::cout << "previous value of atomic bool x - " << z << std::endl;

    std::cout << std::endl;
}

int main()
{
    run_code();
    further_explanation();

    std::cin.get();
    return 0;
}