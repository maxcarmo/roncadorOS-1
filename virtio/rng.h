#ifndef RNG_H
#define RNG_H


#include "../types.h"
#include "virtio.h"

void setup_rng(uint64 addr);

//returns a random number in a certain range defined by [start, end)
//i.e. includes start but doesnt include end
uint32 get_random_number(uint32 start, uint32 end);

typedef struct rng_device{
    uint64 address;
    VirtQ *queue;
    uint32 idx;
}rng_device;


#endif