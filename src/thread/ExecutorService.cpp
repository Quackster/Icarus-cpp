#include "stdafx.h"
#include <iostream>

#include "thread/ExecutorService.h"

ExecutorService::ExecutorService(int threads) {

    if (!this->has_started) {

        this->tasks = new BlockingQueue<Runnable*>();

        for (int i = 0; i < threads; i++) {
            std::thread *new_thread = new_thread = nullptr;
            new_thread = new thread(&ExecutorService::tick, this, new_thread);
        }

        this->has_started = true;
    }
}

ExecutorService *ExecutorService::createSchedulerService(int threads) {
    ExecutorService *service = new ExecutorService(threads);
    service->has_started = false;
    return service;
}

void ExecutorService::schedule(Runnable *runnable) {
    this->tasks->push(runnable);
}


void ExecutorService::tick(thread *thread) {

    while (this->running) {

        if (this->tasks) {

            Runnable *runnable = this->tasks->pop();
            runnable->run();

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        if (!this->running) {
            delete thread;
            delete tasks;
        }
    }
}

ExecutorService::~ExecutorService() {

}