#include "stdafx.h"
#include <iostream>

#include "thread/ExecutorService.h"

/*
    Constructor for executor service, will create threads by amount given

    @param thread pool number
    @return executor service instance
*/
ExecutorService::ExecutorService(int threads) {

    this->tasks = new BlockingQueue<Runnable*>();
    this->threads = new vector<std::thread*>();

    for (int i = 0; i < threads; i++) {
        thread *new_thread = new thread(&ExecutorService::tick, this);
        this->threads->push_back(new_thread);
    }
}

/*
    Create service from statically called method

    @param thread pool number
    @return executor service ptr
*/
ExecutorService *ExecutorService::createSchedulerService(int threads) {
    ExecutorService *service = new ExecutorService(threads);
    return service;
}

/*
    Add Runnable ptr to task for queuing up

    @param runnable ptr
    @return none
*/
void ExecutorService::schedule(Runnable *runnable) {

    this->tasks->push(runnable);
}

/*
    Task for ticking runnables

    @param thread, the thread that was assigned this task
    @return none
*/
void ExecutorService::tick() {

    while (this->running) {

        Runnable *runnable = this->tasks->pop();

        if (runnable != nullptr) {
         
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            runnable->run();
            delete runnable;
        }
    }

    if (!this->running) {

        // Delete all thread ptrs
        for (auto thread : *this->threads) {
            thread->join(); // calling join calls thread deconstructor
        }

        this->threads->clear();

        delete this->threads;
        delete this->tasks;
    }
}

/*
    Deconstructor for executor service

    @return none
*/
ExecutorService::~ExecutorService() {



}