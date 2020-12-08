
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        p2B
// This File:        makeMagic.c
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Spring 2020
//
// Author:           Mei Sun
// Email:            msun252@wisc.edu
// CS Login:         sun
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;     // dimension of the square
    int **msquare; // pointer to heap allocated magic square
} MSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
    int dimension;
    printf("Enter magic square's size (odd integer >=3)\n");
    scanf("%d",&dimension);
    
    if(dimension%2 != 1){
            printf("Size must be odd.\n");
            exit(1);
    }
        
    if(dimension < 3){
	    printf("Size must be >= 3.\n");
           exit(1);
    }

    return dimension;   
} 
   
/* TODO:
 * Makes a magic square of size n using the Siamese algorithm
 * and returns a pointer to the completed MSquare struct.
 *
 * n the number of rosw and columns
 */
MSquare *generateMSquare(int n) {
    
    //pointer pointing to the heap of the struct
    MSquare *ms = malloc(sizeof(MSquare));
    if(ms == NULL){
	    printf("ms is null.\n");
	    exit(1);
    }

    ms->size = n;

    ms->msquare = malloc(sizeof(int*)*n);
    if(ms->msquare == NULL){
       printf("ms->msqare is null.\n");
       exit(1);
    }

    for(int i = 0; i < n; i++){
	   *(ms->msquare + i) = malloc(sizeof(int)*n);
	       if((ms->msquare + i) == NULL){
                    printf("(ms->msquare + i) is null.\n");
                    exit(1);
	       }

    }

    //For checking whether there is already a number here.
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
           *(*(ms->msquare+i)+j) = 0;
        }
    }

    int row = 0, col = (n-1)/2;
    
    //assign 1 to the middle of the first row
    *(*(ms->msquare+row)+col) = 1;
    
    for(int num = 2; num <= n*n; num++){
       
       //if the position now is already in the first row but not last column
       if((row == 0) && (col != n-1)){
          row = n-1;
          col++;
          if(*(*(ms->msquare+row)+col) == 0){
              *(*(ms->msquare+row)+col) = num;
          }
          else{
              row = 1;
              col--;
              *(*(ms->msquare+row)+col) = num;
          }
       }
       
       //if the position now is already in the last column but not first row
       else if((row != 0) && (col == n-1)){
           row--;
           col = 0;
           if(*(*(ms->msquare+row)+col) == 0){
              *(*(ms->msquare+row)+col) = num;
          }
           else{
              row++;
              col = n - 1;
              *(*(ms->msquare+row)+col) = num;
          }
       }
       
       //if the position now is already in the last column and first row
       else if((row == 0) && (col == n-1)){
           row = n-1;
           col = 0;
           if(*(*(ms->msquare+row)+col) == 0){
              *(*(ms->msquare+row)+col) = num;
          }
           else{
              row = 1;
              col = n - 1;
              *(*(ms->msquare+row)+col) = num;
          }
           
       }


       //if the position now is neither in the last column nor first row
       else{
          row--;
          col++;
          if(*(*(ms->msquare+row)+col) == 0){
              *(*(ms->msquare+row)+col) = num;
          }
          else{
            row = row+2;
            col--;
            *(*(ms->msquare+row)+col) = num;
          }
          
       }
       
        
       
       
    }
    
    return ms;    
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * msquare the magic square to output
 * filename the name of the output file
 */
void outputMSquare(MSquare *msquare, char *filename) {
   //create a file that be able to be written
   FILE *fp;
   fp = fopen(filename, "w");

   //check whether fopen() works
   if(fp == NULL){
	   printf("can't open the file: %s.\n",filename);
	   exit(1);
   }
   //write the size and the magic square into the file

   fprintf(fp,"%d\n",msquare->size);
   for(int i = 0; i < msquare->size; i++){		 
	   for(int j = 0;j < msquare->size; j++){
			   fprintf(fp,"%d",*(*(msquare->msquare+i)+j));
			   if(j<(msquare->size-1)){
				   char c = ',';
				   fprintf(fp,"%c",c);
			   }
		  }
		  fprintf(fp, "\n");
	 }
   
   //check whether close the file successfully
   if  (fclose(fp) != 0)
   {
      printf("Error in closeing file.\n");
      exit(1);
   }  

}

/* TODO:
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[]) {
    // TODO: Check input arguments to get output filename
    if(argc != 2){
	    printf("invalid number of arguments.");
	    exit(1);
    }
    // TODO: Get magin square's size from user
       int size = getSize();

    // TODO: Generate the magic square
       MSquare *ms  = generateMSquare(size);

    // TODO: Output the magic square
       outputMSquare(ms , argv[1]);


   //free all of the allocated memory     
    for(int i = 0; i < size; i++){
           free(*(ms->msquare+i));
	   *(ms->msquare+i) = NULL;
    }

    free(ms->msquare);
    ms->msquare = NULL;

    free(ms);
    ms = NULL;




    return 0;
} 


   
