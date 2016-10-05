#pragma once
#include "thread/Runnable.h"

class ExampleRunnable : public Runnable {

public:
    ExampleRunnable(int i);
    void run();
    int i = 0;
};