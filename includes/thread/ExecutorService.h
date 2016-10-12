#pragma once
#include <thread>
#include <vector>

#include "thread/BlockingQueue.h"
#include "thread/Runnable.h"

class ExecutorService
{
public:
    ExecutorService(int threads, std::chrono::milliseconds duration);
    ~ExecutorService();
    
    static ExecutorService *createSchedulerService(int threads);
    static ExecutorService *createSchedulerService(int threads, std::chrono::milliseconds duration);

    void schedule(Runnable* runnable);
    void stop() { std::cout << "called stop func" << std::endl; this->running = false; }

private:
    bool running;
    
    std::chrono::milliseconds duration;
    
    std::vector<std::thread*> threads;
    BlockingQueue<Runnable*> tasks;
    std::vector<std::thread::id> cancelled_threads;

    void tick();
};

