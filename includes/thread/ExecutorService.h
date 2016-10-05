#pragma once
#include <thread>
#include <vector>

#include "thread/BlockingQueue.h"
#include "thread/Runnable.h"

using namespace std;

class ExecutorService
{
public:
    ExecutorService(int threads);
    ~ExecutorService();
    static ExecutorService *createSchedulerService(int threads);
    void schedule(Runnable *runnable);
    void stop() { this->running = false; }
    BlockingQueue<Runnable*> *getTasks() { return tasks; }

private:
    bool running;
    BlockingQueue<Runnable*> *tasks;
    vector<std::thread*> *threads;
    
    void tick();
};

