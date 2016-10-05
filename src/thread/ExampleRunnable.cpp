#include "stdafx.h"

#include "boot/Icarus.h"
#include "thread/ExampleRunnable.h"

ExampleRunnable::ExampleRunnable(int i = 0) {

    this->i = i;
}

void ExampleRunnable::run() {

    this->i++;

    if (i == 4) {
        cout << "topkek " << i << endl;
        Icarus::getGame()->getExecutorService()->stop();
        return;
    }

    //

    ExampleRunnable *new_run = new ExampleRunnable(i);
    Icarus::getGame()->getExecutorService()->schedule(new_run);

}