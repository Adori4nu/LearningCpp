#include <future>
#include <iostream>
#include <thread>

#pragma region future_async_intro
int find_answer_how_old_universe_is()
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    return 5'000;
}

void do_other_calculations()
{
    std::cout << "Do other stuff" << std::endl;
}

void run_code_intro()
{
    std::future<int> the_answer_to_future(std::async(find_answer_how_old_universe_is));
    do_other_calculations();
    std::cout << "Waiting until future.get() obtains result" << std::endl;
    std::cout << "The answer is " << the_answer_to_future.get() << std::endl;
    std::cout << "Result obtained main thread no longer blocked" << std::endl;
}
#pragma endregion

#pragma region future_async_tasks
void printing()
{
    std::cout << "Printing runs on - " << std::this_thread::get_id() << std::endl;
}

int addition(int x, int y)
{
    std::cout << "Addition runs on - " << std::this_thread::get_id() << std::endl;
    return x + y;
}

int substract(int x, int y)
{
    std::cout << "Substraction runs on - " << std::this_thread::get_id() << std::endl;
    return x - y;
}

void run_code_math()
{
    std::cout << "Main thread id - " << std::this_thread::get_id() << std::endl;

    int x{ 100 }, y{ 50 };

    std::future<void> f1(std::async(std::launch::async, printing));
    std::future<int> f2(std::async(std::launch::deferred, addition, x, y));
    std::future<int> f3(std::async(std::launch::async | std::launch::deferred, substract, x, y));

    f1.get();

    std::cout << "Value recieved using f2 future - " << f2.get() << std::endl;
    std::cout << "Value recieved using f3 future - " << f3.get() << std::endl;
}
#pragma endregion

int main()
{
    run_code_intro();
    run_code_math();
}