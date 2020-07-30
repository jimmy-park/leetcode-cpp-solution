// https://leetcode.com/problems/print-in-order/
#pragma once

#include <condition_variable>
#include <functional>
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