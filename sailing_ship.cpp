#include <iostream>
#include <type_traits>
#include "common.hpp"

enum class Captain_Comands : uint16_t
{
    INVALID_COMMAND,
    CLEAN = 1,
    FULL_SPEED = 2,
    STOP_ENGINE = 3,
    PROGRAM_EXIT = 100
};

void cleaning_crew_cleaning()
{
    std::cout << "Cleaning crew starts cleaning." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Cleaning crew finished cleaning." << std::endl;
}

void engine_crew_speeding_up()
{
    std::cout << "Engine crew starts speeding up the engine." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Engine crew achived full speed of the engine." << std::endl;
}

void engine_crew_stopping()
{
    std::cout << "Engine crew starts stopping the engine." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Engine crew stopped the engine." << std::endl;
}

std::ostream &operator<< (std::ostream& os, Captain_Comands& comand)
{
    using enum Captain_Comands;

    switch (comand)
    {
        case CLEAN:
            os << "Clean";
            break;
        case FULL_SPEED:
            os << "Full speed";
            break;
        case STOP_ENGINE:
            os << "Stop engine";
            break;
        case PROGRAM_EXIT:
            os << "Program exit";
            break;
        default:
            os << "Wrong comand";
            break;
    }

    return os;
}

class Captain
{
public:
    Captain() {};

    bool issue_comand(const Captain_Comands& comand)
    {
        using enum Captain_Comands;
        switch (comand)
        {
        case CLEAN:
            {
                std::thread cleaners{ cleaning_crew_cleaning };
                thread_guard cleaners_tg(cleaners, false);   
            }
            return true;
        case FULL_SPEED:
            {
                std::thread engine_crew{ engine_crew_speeding_up };
                thread_guard engine_sp_tg(engine_crew, true);
            }
            return true;
        case STOP_ENGINE:
            {
                std::thread engine_crew{ engine_crew_stopping };
                thread_guard engine_st_tg(engine_crew, true);
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

    void list_the_comands()
    {
        using enum Captain_Comands;
        std::cout << (unsigned long)(CLEAN) << ". To clean" << std::endl;
        std::cout << (unsigned long)(FULL_SPEED) << ". To speed up" << std::endl;
        std::cout << (unsigned long)(STOP_ENGINE) << ". To stop" << std::endl;
        std::cout << (unsigned long)(PROGRAM_EXIT) << ". To exit program" << std::endl;
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

int main()
{
    auto captain = std::make_unique<Captain>();

    bool bIsSailing = true;
    std::cout << "Helo" << std::endl;

    captain->list_the_comands();

    while (bIsSailing)
    {
        uint16_t comand;

        using enum Captain_Comands;

        std::cout << "Please give a comand: ";
        std::cin >> comand;

        bIsSailing = captain->issue_comand(InttoCommand(comand));

    }
}