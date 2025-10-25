#pragma once
// internal/xalloc.h  (do NOT include from public headers)
#ifndef INTERNAL_XALLOC_H
#define INTERNAL_XALLOC_H

#include <stdlib.h>
#include <stdint.h>
#include "fatal.h"
#include "memory_tracker.h"

#define MEM_SCRIPT_INTERPRETER "ScriptInterpreter"
#define MEM_SCRIPT_INSTANCE "ScriptInstance"
#define MEM_SCRIPT_NAVIGATOR "ScriptCodeNavigator"
#define MEM_VARIABLE_COLLECTION "VariableCollection"
#define MEM_VARIABLES "Variables"
#define MEM_STRING_VARIABLE "StringVariable"
#define MEM_VARIABLE_STACK "VariableStack"
#define MEM_VARIABLE_VALUE "VariableValue"
#define MEM_TEST "Test"

#if defined(__GNUC__) || defined(__clang__)
#  define XATTR_NONNULL    __attribute__((returns_nonnull))
#  define XATTR_MALLOC     __attribute__((malloc))
#  define XATTR_ALLOCSZ(i) __attribute__((alloc_size(i)))
#else
#  define XATTR_NONNULL
#  define XATTR_MALLOC
#  define XATTR_ALLOCSZ(i)
#endif

static inline void* xmalloc(const char* origin, size_t n)
XATTR_MALLOC XATTR_NONNULL XATTR_ALLOCSZ(1)
{
    void* p = malloc(n);
    if (!p && n) fatal("Memory allocation.");
#if MEMORY_TRACKER_ENABLED
    track_memory(origin, p);
#endif
    return p;
}

static inline int mul_overflow_size(size_t a, size_t b, size_t* out) {
    if (!a || !b) { *out = 0; return 0; }
    if (a > SIZE_MAX / b) return 1;
    *out = a * b; return 0;
}

static inline void* xreallocarray(void* ptr, size_t n, size_t sz)
XATTR_NONNULL
{
    size_t total;
    if (mul_overflow_size(n, sz, &total)) fatal("Memory allocation.");
    if (total == 0) { free(ptr); return NULL; }
    void* p = realloc(ptr, total);
    if (!p) fatal("Memory allocation.");
    return p;
}

static void xfree(void* ptr)
{
    if (ptr)
    {
#if MEMORY_TRACKER_ENABLED
        untrack_memory(ptr);
#endif
        free(ptr);
    }
}

#endif
