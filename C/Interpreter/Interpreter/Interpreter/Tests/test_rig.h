#pragma once
#include <stdlib.h>
#include <assert.h>

void run_test_rig(void* (*setup)(),
    void (*teardown)(void*),
    void (**tests)(void*));
