#pragma once
#include <thread>

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
    void tick(thread *thread);
    void stop() { this->running = false; }
    BlockingQueue<Runnable*> *getTasks() { return tasks; }

private:
    bool running;
    bool has_started;
    BlockingQueue<Runnable*> *tasks;

};

