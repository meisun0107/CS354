// check for coalesce free space
#include <assert.h>
#include <stdlib.h>
#include "heapAlloc.h"

int main() {
   assert(initHeap(4096) == 0);
   void * ptr[7];

   ptr[0] = allocHeap(500);
   assert(ptr[0] != NULL);
   dumpMem();
   ptr[1] = allocHeap(500);
   assert(ptr[1] != NULL);

   dumpMem();
   ptr[2] = allocHeap(500);
   assert(ptr[2] != NULL);

   dumpMem();
   ptr[3] = allocHeap(500);
   assert(ptr[3] != NULL);

   dumpMem();
   ptr[4] = allocHeap(500);
   assert(ptr[4] != NULL);

   dumpMem();
   ptr[5] = allocHeap(500);
   assert(ptr[5] != NULL);

   dumpMem();
   ptr[6] = allocHeap(500);
   assert(ptr[6] != NULL);

   dumpMem();
   while (allocHeap(500) != NULL)
     ;

   assert(freeHeap(ptr[1]) == 0);
   dumpMem();
   assert(freeHeap(ptr[5]) == 0);
   dumpMem();
   assert(freeHeap(ptr[2]) == 0);
   dumpMem();
   assert(freeHeap(ptr[4]) == 0);
   dumpMem();
   assert(freeHeap(ptr[3]) == 0);
   dumpMem();

   ptr[2] = allocHeap(2500);
   dumpMem();
   assert(ptr[2] != NULL);

   exit(0);
}
