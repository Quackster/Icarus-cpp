/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <thread>
#include <vector>

using std::endl;
using std::cout;

#include "BlockingQueue.h"
#include "Runnable.h"

class ExecutorService
{
public:
    ExecutorService(int threads, std::chrono::milliseconds duration);
    ~ExecutorService();
    
    static ExecutorService *createSchedulerService(int threads);
    static ExecutorService *createSchedulerService(int threads, std::chrono::milliseconds duration);

    void schedule(std::shared_ptr<Runnable> runnable);
    void stop() { cout << "called stop func" << endl; this->running = false; }

private:
    bool running;
    
    std::chrono::milliseconds duration;
    
    std::vector<std::thread*> threads;
    BlockingQueue<std::shared_ptr<Runnable>> tasks;
    std::vector<std::thread::id> cancelled_threads;

    void tick();
};

