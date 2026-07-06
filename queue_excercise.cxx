#include <cstddef>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

template<typename T>
class thread_safe_queue {
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;

public:
    thread_safe_queue() {}

    void push(T new_value) {
        std::shared_ptr<T> data(
            std::make_shared<T>(std::move(new_value))
        );
        std::lock_guard<std::mutex> lock(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res{ data_queue.front() };
        data_queue.pop();
        return res;
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(mut);
        if (data_queue.empty())
            return false;
        value = std::move(*data_queue.front());
        data_queue.pop();
        return true;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mut);
        return data_queue.empty();
    }

    auto size() const -> size_t {
        std::lock_guard<std::mutex> lock(mut);
        return data_queue.size();
    }
};

int main()
{
    thread_safe_queue<int> queue;

    std::thread producer1([&queue]{
        for (int i = 0; i < 10; ++i) {
            std::cout << "Pushing: " << i << " from prod 1\n";
            queue.push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    int value;
    if (queue.try_pop(value))
        std::cout << "Popped value: " << value << std::endl;
    else
        std::cout << "Queue was empty\n";
    if (queue.try_pop(value))
        std::cout << "Popped value: " << value << std::endl;
    else
        std::cout << "Queue was empty\n";

    std::thread producer2([&queue]{
        for (int i = 0; i < 10; ++i) {
            std::cout << "Pushing: " << i << " from prod 2\n";
            queue.push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    if (queue.try_pop(value))
        std::cout << "Popped value: " << value << std::endl;
    else
        std::cout << "Queue was empty\n";
    if (queue.try_pop(value))
        std::cout << "Popped value: " << value << std::endl;
    else
        std::cout << "Queue was empty\n";

    producer1.join();
    producer2.join();
}