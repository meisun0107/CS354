////////////////////////////////////////////////////////////////////////////////
// Main File:        p3
// This File:        heapAlloc.c
// Other Files:      N/A
// Semester:         CS 354 Spring 2020
//
// Author:           Mei Sun
// Email:            msun252@wisc.edu
// CS Login:         sun
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////





///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019-2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////
 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "heapAlloc.h"
 
/*
 * This structure serves as the header for each allocated and free block.
 * It also serves as the footer for each free block but only containing size.
 */
typedef struct blockHeader {           
    int size_status;
    /*
    * Size of the block is always a multiple of 8.
    * Size is stored in all block headers and free block footers.
    *
    * Status is stored only in headers using the two least significant bits.
    *   Bit0 => least significant bit, last bit
    *   Bit0 == 0 => free block
    *   Bit0 == 1 => allocated block
    *
    *   Bit1 => second last bit 
    *   Bit1 == 0 => previous block is free
    *   Bit1 == 1 => previous block is allocated
    * 
    * End Mark: 
    *  The end of the available memory is indicated using a size_status of 1.
    * 
    * Examples:
    * 
    * 1. Allocated block of size 24 bytes:
    *    Header:
    *      If the previous block is allocated, size_status should be 27
    *      If the previous block is free, size_status should be 25
    * 
    * 2. Free block of size 24 bytes:
    *    Header:
    *      If the previous block is allocated, size_status should be 26
    *      If the previous block is free, size_status should be 24
    *    Footer:
    *      size_status should be 24
    */
} blockHeader;         

/* Global variable - DO NOT CHANGE. It should always point to the first block,
 * i.e., the block at the lowest address.
 */
blockHeader *heapStart = NULL;     

/* Size of heap allocation padded to round to nearest page size.
 */
int allocsize;

/*
 * Additional global variables may be added as needed below
 */

//A pointer that pointing to the latest block which has been allocated
blockHeader *preAlloc = NULL;
 
/* 
 * Function for allocating 'size' bytes of heap memory.
 * Argument size: requested size for the payload
 * Returns address of allocated block on success.
 * Returns NULL on failure.
 * This function should:
 * - Check size - Return NULL if not positive or if larger than heap space.
 * - Determine block size rounding up to a multiple of 8 and possibly adding padding as a result.
 * - Use NEXT-FIT PLACEMENT POLICY to chose a free block
 * - Use SPLITTING to divide the chosen free block into two if it is too large.
 * - Update header(s) and footer as needed.
 * Tips: Be careful with pointer arithmetic and scale factors.
 */
void* allocHeap(int size) {     
    //TODO: Your code goes in here.
   
    //check if the size is valid
    if(size <= 0 || size > allocsize){
        return NULL;
    }


    //Determine the round up size
    int padding = 0;
    if ((size + 4) % 8 != 0) {
        padding = 8 - ((size + 4) % 8);
    }
    int roundSize = size + padding +  sizeof(blockHeader);

   

    //use NEXT-FIT to choose a free block
    if(preAlloc == NULL){
	    preAlloc = heapStart;
    }

    blockHeader *ptr = preAlloc;
    blockHeader *next = (blockHeader *) ptr;

    do{
	   int blockSize = ptr->size_status - ptr->size_status % 4;
	   int aBits = ptr->size_status % 2;
	   int pBits = (ptr->size_status % 4) - aBits;

	   if(aBits == 0){
		   if(roundSize == blockSize){
			   //update the current a-bit to 1
			   ptr->size_status = ptr->size_status + 1;
			   //update the next block p-bit to 1
			   next = (blockHeader *) ((void *) ptr + blockSize);
			   next->size_status = next->size_status + 2;
			   preAlloc = ptr;

			   printf("%08x", (unsigned int)(ptr));
			   return (int*)ptr+1;

		   }
	           else if(roundSize < blockSize){
			   ptr->size_status = roundSize;
			   ptr->size_status += 1;
			   printf("%d",ptr->size_status);
			   if(pBits != 0){
				   ptr->size_status = roundSize + 2;
				    ptr->size_status += 1;

			   }
			   preAlloc = ptr;

			   //split the block and update the new block
			   blockHeader *new = (blockHeader *) ((void *) ptr + roundSize);
			   new->size_status = blockSize - roundSize + 2;
                           blockHeader *footer = (blockHeader *)((void*) new + blockSize - roundSize - 4);//consider 4 or 1
			   footer->size_status = blockSize - roundSize;

			   printf("%08x", (unsigned int)(ptr));
			   return (int*)ptr+1;
			


		   }
		   else{
			   //do nothing
		   }

	   }




	   //move to the next header
	   ptr = (blockHeader *) ((void *) ptr + blockSize);

	   //if the pointer reach the end mark, back to the first block of the heap
	   if(ptr->size_status ==1){
		   ptr = heapStart;
	   }
		   
    }while(ptr != preAlloc);


    return NULL;
} 
 
/* 
 * Function for freeing up a previously allocated block.
 * Argument ptr: address of the block to be freed up.
 * Returns 0 on success.
 * Returns -1 on failure.
 * This function should:
 * - Return -1 if ptr is NULL.
 * - Return -1 if ptr is not a multiple of 8.
 * - Return -1 if ptr is outside of the heap space.
 * - Return -1 if ptr block is already freed.
 * - USE IMMEDIATE COALESCING if one or both of the adjacent neighbors are free.
 * - Update header(s) and footer as needed.
 */                    
int freeHeap(void *ptr) {    
    //TODO: Your code goes in here.

    //check if the pointer is NUll or not a mutiple of 8
    if (ptr == NULL || ((int) ptr) % 8 != 0) {
        return -1;
    }

    //check if the block is outside of the heap space
    blockHeader *endMark = (blockHeader *) ptr - 1;
    while (endMark->size_status != 1) {
	//if((endMark->size_status)%4 != 0){
        int temp = (endMark->size_status) - (endMark->size_status) % 4;;
        endMark = (blockHeader *) ((void *) endMark + temp);
	//}
    }
    if ((int) ptr < (int) heapStart || (int) ptr > (int) endMark) {
        return -1;
    }


    blockHeader *freeBlock = (blockHeader *) ptr - 1;
    //check if the block is already been freed
    if(freeBlock->size_status % 2 == 0){
	    return -1;
    }

   
    int currSize = freeBlock->size_status - freeBlock->size_status % 4;//get the size of the current block

    blockHeader *currFooter = (blockHeader *) ((char *) freeBlock + currSize - 4);
    blockHeader *nextHeader = (blockHeader *) ((void *) freeBlock + currSize);//get the header of the next block

    //signal that indicate coalesed with previous block.
   // int preCoalesce = 0;

    //get the p-bit to determine whether to coalese with the previous block or not
    int pBits = (freeBlock->size_status % 4) - 1;
    if (pBits != 0) {
	      //no need to coalese with the previous block
	
        freeBlock->size_status = freeBlock->size_status - 1;//update the current header
       //update the current block's footer
        currFooter->size_status = currSize;  
        nextHeader->size_status = nextHeader->size_status - 2;//update the next block

	
    } 
    else {
        //need to coalesce with the previous block
	blockHeader *preFooter = (blockHeader *) ((void *) freeBlock - 4);
        int totalSize = preFooter->size_status + currSize;

        //update the previous block header
        blockHeader *preHeader = (blockHeader *) ((void *) freeBlock - preFooter->size_status);
	preHeader->size_status += currSize;
	freeBlock = preHeader;

	//update the footer after coalese
        currFooter->size_status = totalSize;
        nextHeader->size_status = nextHeader->size_status - 2;
       // preCoalesce = 1;

    }

    //check if coalesce with next block
    if (nextHeader->size_status % 2 == 0) {
        //need to coalesce with the next block
        blockHeader *current = freeBlock;

        //get current Size
        int nextSize = nextHeader->size_status -( nextHeader->size_status)%4;
        int totalSizeWithNext = currFooter->size_status + nextSize;

	//update the current header
	current->size_status += nextSize;

	//update the new footer
        blockHeader *coalescedFooter = (blockHeader *) ((char *) current + totalSizeWithNext - 4);
        coalescedFooter->size_status = totalSizeWithNext;
    }

    return 0;
} 
 
/*
 * Function used to initialize the memory allocator.
 * Intended to be called ONLY once by a program.
 * Argument sizeOfRegion: the size of the heap space to be allocated.
 * Returns 0 on success.
 * Returns -1 on failure.
 */                    
int initHeap(int sizeOfRegion) {    
 
    static int allocated_once = 0; //prevent multiple initHeap calls
 
    int pagesize;  // page size
    int padsize;   // size of padding when heap size not a multiple of page size
    void* mmap_ptr; // pointer to memory mapped area
    int fd;

    blockHeader* endMark;
  
    if (0 != allocated_once) {
        fprintf(stderr, 
        "Error:mem.c: InitHeap has allocated space during a previous call\n");
        return -1;
    }
    if (sizeOfRegion <= 0) {
        fprintf(stderr, "Error:mem.c: Requested block size is not positive\n");
        return -1;
    }

    // Get the pagesize
    pagesize = getpagesize();

    // Calculate padsize as the padding required to round up sizeOfRegion 
    // to a multiple of pagesize
    padsize = sizeOfRegion % pagesize;
    padsize = (pagesize - padsize) % pagesize;

    allocsize = sizeOfRegion + padsize;

    // Using mmap to allocate memory
    fd = open("/dev/zero", O_RDWR);
    if (-1 == fd) {
        fprintf(stderr, "Error:mem.c: Cannot open /dev/zero\n");
        return -1;
    }
    mmap_ptr = mmap(NULL, allocsize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == mmap_ptr) {
        fprintf(stderr, "Error:mem.c: mmap cannot allocate space\n");
        allocated_once = 0;
        return -1;
    }
  
    allocated_once = 1;

    // for double word alignment and end mark
    allocsize -= 8;

    // Initially there is only one big free block in the heap.
    // Skip first 4 bytes for double word alignment requirement.
    heapStart = (blockHeader*) mmap_ptr + 1;

    // Set the end mark
    endMark = (blockHeader*)((void*)heapStart + allocsize);
    endMark->size_status = 1;

    // Set size in header
    heapStart->size_status = allocsize;

    // Set p-bit as allocated in header
    // note a-bit left at 0 for free
    heapStart->size_status += 2;

    // Set the footer
    blockHeader *footer = (blockHeader*) ((void*)heapStart + allocsize - 4);
    footer->size_status = allocsize;
  
    return 0;
} 
                  
/* 
 * Function to be used for DEBUGGING to help you visualize your heap structure.
 * Prints out a list of all the blocks including this information:
 * No.      : serial number of the block 
 * Status   : free/used (allocated)
 * Prev     : status of previous block free/used (allocated)
 * t_Begin  : address of the first byte in the block (where the header starts) 
 * t_End    : address of the last byte in the block 
 * t_Size   : size of the block as stored in the block header
 */                     
void dumpMem() {     
 
    int counter;
    char status[5];
    char p_status[5];
    char *t_begin = NULL;
    char *t_end   = NULL;
    int t_size;

    blockHeader *current = heapStart;
    counter = 1;

    int used_size = 0;
    int free_size = 0;
    int is_used   = -1;

    fprintf(stdout, "************************************Block list***\
                    ********************************\n");
    fprintf(stdout, "No.\tStatus\tPrev\tt_Begin\t\tt_End\t\tt_Size\n");
    fprintf(stdout, "-------------------------------------------------\
                    --------------------------------\n");
  
    while (current->size_status != 1) {
        t_begin = (char*)current;
        t_size = current->size_status;
    
        if (t_size & 1) {
            // LSB = 1 => used block
            strcpy(status, "used");
            is_used = 1;
            t_size = t_size - 1;
        } else {
            strcpy(status, "Free");
            is_used = 0;
        }

        if (t_size & 2) {
            strcpy(p_status, "used");
            t_size = t_size - 2;
        } else {
            strcpy(p_status, "Free");
        }

        if (is_used) 
            used_size += t_size;
        else 
            free_size += t_size;

        t_end = t_begin + t_size - 1;
    
        fprintf(stdout, "%d\t%s\t%s\t0x%08lx\t0x%08lx\t%d\n", counter, status, 
        p_status, (unsigned long int)t_begin, (unsigned long int)t_end, t_size);
    
        current = (blockHeader*)((char*)current + t_size);
        counter = counter + 1;
    }

    fprintf(stdout, "---------------------------------------------------\
                    ------------------------------\n");
    fprintf(stdout, "***************************************************\
                    ******************************\n");
    fprintf(stdout, "Total used size = %d\n", used_size);
    fprintf(stdout, "Total free size = %d\n", free_size);
    fprintf(stdout, "Total size = %d\n", used_size + free_size);
    fprintf(stdout, "***************************************************\
                    ******************************\n");
    fflush(stdout);

    return;  
} 
