#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

bool have_i_arrived{ false };
int distance_to_my_destination{ 10 }
, distance_coverd{ 0 };

#pragma region cv_intro
bool keep_driving()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1'000));
        distance_coverd++;
    }

    return false;
}

void keep_awake_all_night()
{
    while (distance_coverd < distance_to_my_destination)
    {
        std::cout << "Keep check, whether I am there." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1'000));
    }
    std::cout << "Finally I am there, distance_covered = " << distance_coverd << std::endl;
}

void set_the_alarm_and_take_a_nap()
{
    if (distance_coverd < distance_to_my_destination)
    {
        std::cout << "Let me take a nap." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10'000));
    }
    std::cout << "Finally I am there, distance covered = " << distance_coverd << std::endl;
}

void run_code()
{
    std::thread driver_thread(keep_driving);
    std::thread keep_awake_all_night_thread(keep_awake_all_night);
    std::thread set_the_alarm_and_take_a_nap_thread(set_the_alarm_and_take_a_nap);

    keep_awake_all_night_thread.join();
    set_the_alarm_and_take_a_nap_thread.join();
    driver_thread.join();
}
#pragma endregion

#pragma region condition variable example
bool have_i_arrived_cv{ false };
int total_distance{ 10 }, distance_coverd_cv{ 0 };
std::condition_variable cv;
std::mutex m;

void keep_moving()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1'000));
        distance_coverd_cv++;

        if (distance_coverd_cv == total_distance)
        {
            cv.notify_one();
        }
    }
}

void ask_driver_to_wake_u_up_at_right_time()
{
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul, [] { return distance_coverd_cv == total_distance; });
    std::cout << "finally I am there, distance_covered_cv = " << distance_coverd_cv << std::endl;
}

void run_code_cv_example()
{
    std::thread driver_thread(keep_moving);
    std::thread passenger_thread(ask_driver_to_wake_u_up_at_right_time);

    passenger_thread.join();
    driver_thread.join();
}
#pragma endregion

int main()
{
    // run_code();
    std::cout << "=== CV example below ===" << std::endl;
    run_code_cv_example();
}