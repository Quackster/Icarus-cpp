#include "stdafx.h"

#include "boot/Icarus.h"
#include "thread/ExampleRunnable.h"

ExampleRunnable::ExampleRunnable(int i = 0) {

    this->i = i;
}

void ExampleRunnable::run() {

    this->i++;

    cout << "topkek " << i << endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    ExampleRunnable *new_run = new ExampleRunnable(i);
    Icarus::getGame()->getExecutorService()->schedule(new_run);
}