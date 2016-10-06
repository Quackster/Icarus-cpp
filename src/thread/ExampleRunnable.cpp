#include "stdafx.h"

#include "boot/Icarus.h"
#include "thread/ExampleRunnable.h"

ExampleRunnable::ExampleRunnable(int i) {

    this->i = i;
}

void ExampleRunnable::run() {

    this->i++;

    cout << "Threaded task: " << i << endl;

    ExampleRunnable *newRunnable = new ExampleRunnable(i);
    Icarus::getGame()->getGameScheduler()->schedule(newRunnable);

}