#include "stdafx.h"

#include "boot/Icarus.h"
#include "thread/ExampleRunnable.h"

ExampleRunnable::ExampleRunnable(int i) {

    this->i = i;
}

void ExampleRunnable::run() {

    this->i++;

    std::cout << "Threaded task: " << i << std::endl;

}