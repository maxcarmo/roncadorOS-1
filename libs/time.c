#include "time.h"
#include "../memlayout.h"

void wait(uint32 ms){
    uint64 time = (*(uint64*) CLINT_MTIME) / 10000;
    uint64 new_time = time;
    while (new_time - time < ms){
        new_time = (*(uint64*) CLINT_MTIME) / 10000;
    }
}