#include <iostream>
#include <thread>
#include <queue>
#include <functional>

enum class Captain_Comands : uint16_t
{
    INVALID_COMMAND,
    CLEAN = 1,
    FULL_SPEED = 2,
    STOP_ENGINE = 3,
    PROGRAM_EXIT = 100
};

static std::queue<std::function<void()>> engine_work_queue;
static std::queue<std::function<void()>> cleaning_work_queue;

auto cleanShip() -> void
{
    std::cout << "Cleaning the ship." << std::endl;
}

auto fullSpeedAhead() -> void
{
    std::cout << "Full Speed Ahead." << std::endl;
}

auto stopShip() -> void
{
    std::cout << "Stopping the ship." << std::endl;
}

class Captain
{
public:
    Captain()
        {};

    bool issue_comand(const Captain_Comands& comand)
    {
        using enum Captain_Comands;
        switch (comand)
        {
        case CLEAN:
            {
                cleaning_work_queue.emplace(cleanShip);
            }
            return true;
        case FULL_SPEED:
            {
                engine_work_queue.emplace(fullSpeedAhead);
            }
            return true;
        case STOP_ENGINE:
            {
                engine_work_queue.emplace(stopShip);
            }
            return true;
        case PROGRAM_EXIT:
            std::cout << "Docking the ship in to main!" << std::endl;
            return false;
        default:
            std::cout << "Invalid comand." << std::endl;
            return true;
        }
    }
};

Captain_Comands InttoCommand(std::uint16_t input)
{
    using enum Captain_Comands;
    Captain_Comands retVal = INVALID_COMMAND;
    switch(static_cast<Captain_Comands>(input))
    {
        case CLEAN:
            retVal = CLEAN;
            break;
        case FULL_SPEED:
            retVal = FULL_SPEED;
            break;
        case STOP_ENGINE:
            retVal = STOP_ENGINE;
            break;
        case PROGRAM_EXIT:
            retVal = PROGRAM_EXIT;
            break;
        default: retVal = INVALID_COMMAND;
            break;
    }
    return retVal;
}

void list_the_comands()
{
    using enum Captain_Comands;
    std::cout << (unsigned long)(CLEAN) << ". To clean" << std::endl;
    std::cout << (unsigned long)(FULL_SPEED) << ". To speed up" << std::endl;
    std::cout << (unsigned long)(STOP_ENGINE) << ". To stop" << std::endl;
    std::cout << (unsigned long)(PROGRAM_EXIT) << ". To exit program" << std::endl;
    std::cout << std::endl;
}

int main()
{
    using namespace std::chrono_literals;

    auto captain = Captain{};

    bool bIsSailing = true;
    uint16_t user_comand;

    std::thread engine_crew
    {
        [&bIsSailing](){
            while (bIsSailing)
            {
                if(!engine_work_queue.empty())
                {
                    engine_work_queue.front()();
                    engine_work_queue.pop();
                    std::this_thread::sleep_for(1s);
                }
                else
                {
                    std::cout << "Engine crew sleeping no work to be done here." << std::endl;
                    std::this_thread::sleep_for(2s);
                }
            }
            std::cout << "Engine work thread Quitting" << std::endl;
        }
    };

    std::thread cleaning_crew
    {
        [&bIsSailing](){
            while (bIsSailing)
            {
                if(!cleaning_work_queue.empty())
                {
                    cleaning_work_queue.front()();
                    cleaning_work_queue.pop();
                    std::this_thread::sleep_for(1s);
                }
                else
                {
                    std::cout << "Cleaning crew sleeping no work to be done here." << std::endl;
                    std::this_thread::sleep_for(2s);
                }
            }
            std::cout << "Cleaning work thread Quitting" << std::endl;
        }
    };

    while (bIsSailing)
    {
        list_the_comands();

        using enum Captain_Comands;
        std::cout << "Please give a comand: ";
        std::cin >> user_comand;

        bIsSailing = captain.issue_comand(InttoCommand(user_comand));
        if (!engine_work_queue.empty()) std::cout << "There is work to do!" << std::endl;
    }

    if(engine_crew.joinable()) engine_crew.join();
    if(cleaning_crew.joinable()) cleaning_crew.join();

    return EXIT_SUCCESS;
}