/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include <algorithm>

#include "ExecutorService.h"

/*
    Constructor for executor service, will create threads by amount given

    @param thread pool number
    @return executor service instance
*/
ExecutorService::ExecutorService(int threads, std::chrono::milliseconds duration) : duration(duration) {

    //this->tasks = BlockingQueue<std::shared_ptr<Runnable>>();
    //threads = std::vector<std::thread*>();

    this->running = true;

    for (int i = 0; i < threads; i++) {
        if (this->running) {
            this->threads.push_back(new std::thread(&ExecutorService::tick, this));
        }
    }
}

/*
    Create service from statically called method, if no duration is specified,
    it will default to tick every 500ms

    @param thread pool number
    @return executor service ptr
*/
ExecutorService *ExecutorService::createSchedulerService(int threads) {
    ExecutorService *service = new ExecutorService(threads, std::chrono::milliseconds(500));
    return service;
}

/*
Create service from statically called method with duration specified

@param thread pool number
@param duration
@return executor service ptr
*/
ExecutorService *ExecutorService::createSchedulerService(int threads, std::chrono::milliseconds duration) {
    ExecutorService *service = new ExecutorService(threads, duration);
    return service;
}

/*
    Add Runnable ptr to task for queuing up

    @param runnable ptr
    @return none
*/
void ExecutorService::schedule(std::shared_ptr<Runnable> runnable) {
    this->tasks.push(runnable);
}

/*
    Task for ticking runnables

    @param thread, the thread that was assigned this task
    @return none
*/
void ExecutorService::tick() {

    while (this->running) {

        std::shared_ptr<Runnable> runnable = this->tasks.pop();

        if (runnable != nullptr) {
            std::this_thread::sleep_for(this->duration);
            runnable->run();
        }

        // stop() function was called, try to cancel as soon as possible.
        if (!this->running) {
            this->cancelled_threads.push_back(std::this_thread::get_id());
        }
    }

    if (!this->running) {

        bool stop_yet = false;

        for (std::thread *thread : this->threads) {

            // If our thread isn't in this list, then we can't stop yet! :(
            if (std::find(this->cancelled_threads.begin(), this->cancelled_threads.end(), thread->get_id()) != this->cancelled_threads.end()) {
                stop_yet = true;
            }
            else {
                // Can't stop yet because other threads aren't done finishing tasks.
                stop_yet = false;
                return;
            }
        }

        // We can finally stop :D
        if (stop_yet) {
            
            for (auto thread : this->threads) {
                thread->detach();
            }

            for (auto thread : this->threads) {
                delete thread;
            }
        }
    }
}

/*
    Deconstructor for executor service

    @return none
*/
ExecutorService::~ExecutorService() {



}