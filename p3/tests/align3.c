// many odd sized allocations checked for alignment
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "heapAlloc.h"

int main() {
    assert(initHeap(4096) == 0);
    void* ptr[9];
    ptr[0] = allocHeap(1);
    dumpMem();
    ptr[1] = allocHeap(5);
    dumpMem();

    ptr[2] = allocHeap(14);
    dumpMem();

    ptr[3] = allocHeap(8);
    dumpMem();

    ptr[4] = allocHeap(1);
    dumpMem();

    ptr[5] = allocHeap(4);
    dumpMem();

    ptr[6] = allocHeap(9);
    dumpMem();

    ptr[7] = allocHeap(33);
    dumpMem();

    ptr[8] = allocHeap(55);
    dumpMem();

   
    for (int i = 0; i < 9; i++) {
        assert(ptr[i] != NULL);
    }

    for (int i = 0; i < 9; i++) {
        assert(((int)ptr[i]) % 8 == 0);
    }
    exit(0);
}
