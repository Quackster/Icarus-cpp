#pragma once
#include <thread>
#include <mutex>
#include <iostream>
#include <deque>
#include <string>
#include <functional>
#include <iostream>

using namespace std;

template <typename T>
class BlockingQueue {
private:
    mutex mutex_;
    deque<T> queue_;

public:
    T pop() {
        this->mutex_.lock();
        T value = this->queue_.front();
        this->queue_.pop_front();
        this->mutex_.unlock();
        return value;
    }

    void push(T value) {
        this->mutex_.lock();
        this->queue_.push_back(value);
        this->mutex_.unlock();
    }

    bool empty() {
        this->mutex_.lock();
        bool check = this->queue_.empty();
        this->mutex_.unlock();
        return check;
    }

    deque<T> getQueue() {
        return queue_;
    }
};