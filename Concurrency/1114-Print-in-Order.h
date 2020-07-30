// https://leetcode.com/problems/print-in-order/

#pragma once

#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>

class PrintInOrder {
public:
    void first(std::function<void()> printFirst)
    {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();

        {
            // prevent lost wakeup and spurious wakeup
            // and with CTAD (since C++17), you don't need to type std::mutex as template argument
            std::lock_guard lock { mutex_ };
            done_first_ = true;
        }

        cv_.notify_all();
    }

    void second(std::function<void()> printSecond)
    {
        {
            std::unique_lock lock { mutex_ };
            cv_.wait(lock, [this] { return done_first_; });
        }

        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();

        {
            std::lock_guard lock { mutex_ };
            done_second_ = true;
        }

        cv_.notify_one();
    }

    void third(std::function<void()> printThird)
    {
        {
            std::unique_lock lock { mutex_ };
            cv_.wait(lock, [this] { return done_second_; });
        }

        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }

private:
    bool done_first_ { false };
    bool done_second_ { false };
    mutable std::mutex mutex_;
    std::condition_variable cv_;
};

void TC1114(std::vector<int> input)
{
    std::cout << "[INPUT]  ";
    for (auto i : input) {
        std::cout << i;
    }
    std::cout << std::endl;

    PrintInOrder pio;
    auto first = [&pio] { return pio.first([] { std::cout << "first"; }); };
    auto second = [&pio] { return pio.second([] { std::cout << "second"; }); };
    auto third = [&pio] { return pio.third([] { std::cout << "third"; }); };

    std::cout << "[OUTPUT] ";

    std::vector<std::future<void>> tasks;

    for (auto i : input) {
        if (i == 1)
            tasks.emplace_back(std::async(std::launch::async, first));
        else if (i == 2)
            tasks.emplace_back(std::async(std::launch::async, second));
        else if (i == 3)
            tasks.emplace_back(std::async(std::launch::async, third));
    }

    for (auto& task : tasks)
        task.get();

    std::cout << std::endl;
}

void Run1114()
{
    std::cout << "Run Problem 1114" << std::endl;

    TC1114({ 1, 2, 3 });
    TC1114({ 1, 3, 2 });
    TC1114({ 2, 1, 3 });
    TC1114({ 2, 3, 1 });
    TC1114({ 3, 1, 2 });
    TC1114({ 3, 2, 1 });

    std::cout << std::endl;
}