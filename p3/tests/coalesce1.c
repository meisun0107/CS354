// check for coalesce free space
#include <assert.h>
#include <stdlib.h>
#include "heapAlloc.h"

int main() {
   assert(initHeap(4096) == 0);
   void * ptr[4];

   ptr[0] = allocHeap(800);
   assert(ptr[0] != NULL);
   dumpMem();
   ptr[1] = allocHeap(800);
   assert(ptr[1] != NULL);
   dumpMem();
   ptr[2] = allocHeap(800);
   assert(ptr[2] != NULL);
   dumpMem();
   ptr[3] = allocHeap(800);
   assert(ptr[3] != NULL);
   dumpMem();
   while (allocHeap(800) != NULL)
     ;

   assert(freeHeap(ptr[1]) == 0);
   dumpMem();
   assert(freeHeap(ptr[2]) == 0);
   dumpMem();

   ptr[2] = allocHeap(1600);
   assert(ptr[2] != NULL);
   dumpMem();

   exit(0);
}
