// many odd sized allocations
#include <assert.h>
#include <stdlib.h>
#include "heapAlloc.h"

int main() {
   assert(initHeap(4096) == 0);
   assert(allocHeap(1) != NULL);
   dumpMem();
   assert(allocHeap(5) != NULL);
   dumpMem();
   assert(allocHeap(14) != NULL);
   assert(allocHeap(8) != NULL);
   assert(allocHeap(1) != NULL);
   assert(allocHeap(4) != NULL);
   dumpMem();
   assert(allocHeap(9) != NULL);
   assert(allocHeap(33) != NULL);
   dumpMem();
   assert(allocHeap(55) != NULL);
   dumpMem();
   exit(0);
}
