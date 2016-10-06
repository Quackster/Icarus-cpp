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
    void schedule(std::shared_ptr<Runnable> runnable);
    void stop() { this->running = false; }
    BlockingQueue<std::shared_ptr<Runnable>> *getTasks() { return tasks; }

private:
    bool running;

    std::chrono::milliseconds duration;
    BlockingQueue<std::shared_ptr<Runnable>> *tasks;
    std::vector<std::thread*> *threads;
    
    void tick();
};

