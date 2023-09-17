#pragma once

#include <vector>
#include <thread>

class thread_guard {

    std::thread& t;
    bool joinability;
public:
    explicit thread_guard(std::thread& _t, bool _joinability) : t(_t), joinability(_joinability) {}

    ~thread_guard()
    {
        if (t.joinable())
        {
            if (joinability) t.join();
            else t.detach();
        }
    }

    thread_guard(const thread_guard& _t) = delete; // copy constructor deleted
    thread_guard& operator= (const thread_guard& _t) = delete; // copy assingment deleted
    
};