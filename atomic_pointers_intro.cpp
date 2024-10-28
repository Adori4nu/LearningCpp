#include <atomic>
#include <iostream>
#include <thread>

auto run_code() -> void
{
    int values[20];

    for (int i{0}; i < 20; ++i)
    {
        values[i] = i+1;
    }

    std::atomic<int*> x_pointer = values;
    std::cout << "Is atomic integer pointer lock free? "
         << (x_pointer ? "yes" : "no") << std::endl;

    int* y_pointer = values + 3;

    x_pointer.store(y_pointer);
    std::cout << "value refered by pointer : " << *(x_pointer.load()) << std::endl;

    bool ret_val{ x_pointer.compare_exchange_weak(y_pointer, values + 10) };
    std::cout << "store operation successfull : " << (ret_val ? "yes" : "no") << std::endl;
    std::cout << "new value pointer by atomic pointer : " << *x_pointer << std::endl;


    x_pointer.store(values);
    std::cout << "1. After store value pointed by atomic pointer - " << *x_pointer << std::endl;

    int* prev_pointer_val_1 = x_pointer.fetch_add(12);

    std::cout << "2. After fetch add previous value pointed by atomic pointer - "
         << *prev_pointer_val_1 << std::endl;
    std::cout << "2. After fetch add new value pointed by atomic pointer      - "
         << *x_pointer << std::endl;

    int* prev_pointer_val_2 = x_pointer.fetch_sub(3);
    
    std::cout << "3. After fetch sub previous value pointed by atomic pointer - "
         << *prev_pointer_val_2 << std::endl;
    std::cout << "3. After fetch sub new value pointed by atomic pointer      - "
         << *x_pointer << std::endl;

    x_pointer++;
    std::cout << "4. After post increment value pointed by atomic pointer     - "
         << *x_pointer << std::endl;
    
    x_pointer--;
    std::cout << "5. After post decrement value pointed by atomic pointer     - "
         << *x_pointer << std::endl;
}

int main()
{
    run_code();

    std::cin.get();
    return 0;
}