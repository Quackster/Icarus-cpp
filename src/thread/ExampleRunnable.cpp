#include "stdafx.h"

#include "boot/Icarus.h"
#include "thread/ExampleRunnable.h"

ExampleRunnable::ExampleRunnable(int i = 0) {

    this->i = i;
}

void ExampleRunnable::run() {

    this->i++;

    cout << "Threaded task: " << i << endl;

    ExampleRunnable *new_run = new ExampleRunnable(i);
    Icarus::getGame()->getGameScheduler()->schedule(new_run);

}