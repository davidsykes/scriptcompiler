#include "test_rig.h"


void run_test_rig(void* (*setup)(),
    void (*teardown)(void*),
    void (**tests)(void*))
{
    int test = 0;
    while (tests[test])
    {
        void* context = setup();
        tests[test](context);
        teardown(context);
        track_memory_allocations();

        ++test;
    }

}