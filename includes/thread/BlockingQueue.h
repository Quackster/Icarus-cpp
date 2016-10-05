#pragma once
#include <thread>
using std::thread;
#include <mutex>
using std::mutex;
#include <iostream>
using std::cout;
using std::endl;
#include <queue>
using std::queue;
#include <string>
using std::string;
using std::to_string;
#include <functional>
using std::ref;

template <typename T>
class BlockingQueue {
private:
    mutex mutex_;
    queue<T> queue_;

public:
    T pop() {
        this->mutex_.lock();
        T value;

        if (!this->queue_.empty()) {
            value = this->queue_.front();
            this->queue_.pop();
        }

        this->mutex_.unlock();
        return value;
    }

    void push(T value) {
        this->mutex_.lock();
        this->queue_.push(value);
        this->mutex_.unlock();
    }

    bool empty() {
        this->mutex_.lock();
        bool check = this->queue_.empty();
        this->mutex_.unlock();
        return check;
    }

    queue<T> getQueue() {
        return queue_;
    }
};