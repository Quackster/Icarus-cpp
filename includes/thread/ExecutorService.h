#pragma once
#include <thread>
#include <vector>

#include "thread/BlockingQueue.h"
#include "thread/Runnable.h"

using namespace std;

class ExecutorService
{
public:
    ExecutorService(int threads, chrono::milliseconds duration);
    ~ExecutorService();
    static ExecutorService *createSchedulerService(int threads);
    static ExecutorService *createSchedulerService(int threads, chrono::milliseconds duration);
    void schedule(Runnable *runnable);
    void stop() { this->running = false; }
    BlockingQueue<Runnable*> *getTasks() { return tasks; }

private:
    bool running;

    chrono::milliseconds duration;
    BlockingQueue<Runnable*> *tasks;
    vector<std::thread*> *threads;
    
    void tick();
};

