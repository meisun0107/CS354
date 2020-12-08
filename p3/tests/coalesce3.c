// check for coalesce free space
#include <assert.h>
#include <stdlib.h>
#include "heapAlloc.h"

int main() {
   assert(initHeap(4096) == 0);
   void * ptr[5];

   ptr[0] = allocHeap(600);
   assert(ptr[0] != NULL);

   dumpMem();

   ptr[1] = allocHeap(600);
   assert(ptr[1] != NULL);

   dumpMem();
   ptr[2] = allocHeap(600);
   assert(ptr[2] != NULL);

   ptr[3] = allocHeap(600);
   assert(ptr[3] != NULL);

   dumpMem();
   ptr[4] = allocHeap(600);
   assert(ptr[4] != NULL);

   dumpMem();
   while (allocHeap(600) != NULL)
     ;

   assert(freeHeap(ptr[1]) == 0);
   dumpMem();
   assert(freeHeap(ptr[3]) == 0);
   dumpMem();
   assert(freeHeap(ptr[2]) == 0);

   dumpMem();
   ptr[2] = allocHeap(1800);
   assert(ptr[2] != NULL);

   dumpMem();
   exit(0);
}
