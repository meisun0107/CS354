///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        P2A
// This File:        n_in_a_row
// Other Files:     
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
     
char *COMMA = ",";  
     
/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size) {      
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1) {
        printf("Error in reading the file.\n");
        exit(1);
    }

    char *token = NULL;
    token = strtok(line, COMMA);
    *size = atoi(token);
}       
 
   
  
/* TODO:
 * Returns 1 if and only if the board is in a valid state.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * size: number of rows and columns
 */
int n_in_a_row(int **board, int size) {
  
    //two variables for counting number of Xs and Os on the board 
    int countX = 0, countO = 0;
   
    //check whether n is odd
    if(size%2 == 0){
	    return 0;
    }
    
    //check whether the number of O and X are equal or with difference of 1
    for(int i = 0; i < size; i++){
	    for(int j = 0; j < size; j++){
		    if(*(*(board + i) + j)==1) countX++;       
	            if(*(*(board + i) + j)==2) countO++;
		    }  
    }
    if(countX != countO && countX-countO != 1 && countO-countX != 1){
	    return 0;
    }

    
    //check whether the board have no winner or just one winner
    
    //check the winning lines of rows for X and O
    int rowWinsX = 0,rowWinsO = 0,X = 0,O = 0;
    for(int k = 0; k < size; k++){
	    X=0;
	    O=0;
	    for(int h = 0; h < size; h++){
		    if(*(*(board + k) + h)==1) X++;
                    if(*(*(board + k) + h)==2) O++;
	    }
	    if(X==size)rowWinsX++;
	    if(O==size)rowWinsO++;

    }

    //check the winning lines of columns for X and O
    int colWinsX = 0, colWinsO = 0;
    for(int k = 0; k < size; k++){
            X=0;
            O=0;
            for(int h = 0; h < size; h++){
                    if(*(*(board + h) + k)==1) X++;
                    if(*(*(board + h) + k)==2) O++;
            }
            if(X==size)colWinsX++;
            if(O==size)colWinsO++;

    }

    //check the winning lines of diagonals for X and O
    X=0;
    O=0;
    int diaWinsX = 0, diaWinsO = 0;
    for(int k = 0; k < size; k++){
            if(*(*(board+k)+k)==1) X++;
	    if(*(*(board+k)+k)==2) O++;
    }
    if(X==size)diaWinsX++;
    if(O==size)diaWinsO++;


    //check the winning lines of opposite diagonals for X and O
    X=0;
    O=0;
    int OpdiaWinsX = 0,OpdiaWinsO = 0;
    for(int k = 0; k < size; k++){
	    int h = size - k-1;
            if(*(*(board+h)+k)==1) X++;
            if(*(*(board+h)+k)==2) O++;
    }
    if(X==size)OpdiaWinsX++;
    if(O==size)OpdiaWinsO++;

   //get how many winning lines each person has
   int  numWinsX = OpdiaWinsX + diaWinsX + colWinsX + rowWinsX;
   int  numWinsO = OpdiaWinsO + diaWinsO + colWinsO + rowWinsO;

   //get how many winning lines are there totally 
   int numWins = numWinsX + numWinsO;

   //check if there are  any situations that one person has two winning lines intersected
  
   //while X is the winner
   if(numWinsO == 0 && numWins == 2){
	   if(OpdiaWinsX==1 && diaWinsX==1){
		   return 1;
	   }
	   if(OpdiaWinsX==1 && colWinsX==1){
		   return 1;
	   }
	   if(OpdiaWinsX==1 && rowWinsX==1){
		   return 1;
	   }
	   if(diaWinsX==1 && colWinsX==1){
	     	  return 1;
	   }
	   if(diaWinsX==1 && rowWinsX==1){
		   return 1;
	   }
           if(colWinsX==1 && colWinsX==1){
		   return 1;
	   }
   } 

   //while O is the winner
   if(numWinsX == 0 && numWins == 2){
           if(OpdiaWinsO==1 && diaWinsO==1){
		   return 1;
	   }
	   if(OpdiaWinsO==1 && colWinsO==1){
		   return 1;
	   }
	   if(OpdiaWinsO==1 && rowWinsO==1){
		   return 1;
	   }
	   if(diaWinsO==1 && colWinsO==1){
		   return 1;
	   }
	   if(diaWinsO==1 && rowWinsO==1){
		   return 1;
	   }
	   if(colWinsO==1 && colWinsO==1){
                   return 1;
	   }
   }


   //check whether there are more winners
   if(numWins!=0 && numWins!=1){
	    return 0;
    }

    return 1;   
}    
  

   
/* PARTIALLY COMPLETED:
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {              
     
    //TODO: Check if number of command-line arguments is correct.
    if (argc != 2) {
        fprintf(stderr, "Usage: decode inputfile \n");
        exit(1);
    }
    //Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    //Declare local variables.
    int size;

    //TODO: Call get_dimensions to retrieve the board size.
    get_dimensions(fp, &size);

    //TODO: Dynamically allocate a 2D array of dimensions retrieved above.
    int **board = malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++) {
        *(board + i) = malloc(sizeof(int) * size);
    }
    //Read the file line by line.
    //Tokenize each line wrt comma to store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading the file.\n");

            exit(1);
        }

        token = strtok(line, COMMA);
        for (int j = 0; j < size; j++) {
            //TODO: Complete the line of code below
            //to initialize your 2D array.
            *(*(board + i) + j)  = atoi(token);
            token = strtok(NULL, COMMA);
        }
    }

    //TODO: Call the function n_in_a_row and print the appropriate
    //output depending on the function's return value.
    int x = n_in_a_row(board, size);
    if (x == 1){
        printf("valid\n");
    }
    else{
        printf("invalid\n");
    }
     
    //TODO: Free all dynamically allocated memory.
    for (int i = 0; i < size; i++) {
        free(*(board + i));
    }
    free(board);

    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    } 
     
    return 0;       
}       
