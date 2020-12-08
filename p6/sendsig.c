////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        sendsig.c
// Other Files:      division.c
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

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>


/*sending signals (SIGINT and SIGUSR1) to other programs using their pid
 *argc: total number of arguments
 **argv[]: pointers pointing to the arguments
 */
int main(int argc, char *argv[]){

    if(argc != 3){
	    printf("Usage: <signal type> <pid>\n");
       return 0;
    }

    if(strcmp(argv[1],"-u") == 0){
    	if(kill(atoi(argv[2]),SIGUSR1) == -1){
		printf("Error in kill().\n");
		exit(1);
	}

    }
    
    else if(strcmp(argv[1],"-i") == 0){
    	if(kill(atoi(argv[2]),SIGINT) == -1){
		printf("Error in kill().\n");
		exit(1);
	}	

    }
    
    else{
    	printf("<signal type> = -u or -i\n");
    }
}
