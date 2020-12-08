// check for coalesce free space (last chunk)
#include <assert.h>
#include <stdlib.h>
#include "heapAlloc.h"

#define HEADER (4)
#define SLACK (8)

int main() {
   assert(initHeap(4096) == 0);
   void * ptr[4];

   ptr[0] = allocHeap(884);
   assert(ptr[0] != NULL);
   dumpMem();
   ptr[1] = allocHeap(884);
   assert(ptr[1] != NULL);

   dumpMem();
   ptr[2] = allocHeap(884);
   assert(ptr[2] != NULL);

   dumpMem();
   ptr[3] = allocHeap(884);
   assert(ptr[3] != NULL);

   dumpMem();
   assert(allocHeap(884) == NULL);
   
   // last free chunk is at least this big
   int free = (4096 - (884 + HEADER) * 4) - SLACK;

   dumpMem();
   assert(freeHeap(ptr[3]) == 0);
   free += (884 + HEADER);
   dumpMem();
   ptr[3] = allocHeap(free - HEADER - 40);
   dumpMem();
   assert(ptr[3] != NULL);
   exit(0);
}
