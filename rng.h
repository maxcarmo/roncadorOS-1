#include "types.h"
#include "virtio.h"

void setup_rng(uint64 addr);
uint32 get_random_number(uint32 start, uint32 end);

typedef struct rng_device{
    uint64 address;
    VirtQ *queue;
    uint32 idx;
}rng_device;