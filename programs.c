#include "types.h"

extern void msg_syscall(int);

__attribute__((aligned(4096)))
void
code1(void) {
     uint64 i;
    while(1) {
        for(i = 0; i < 100000000; i++);
        msg_syscall(7);
    }
    
}