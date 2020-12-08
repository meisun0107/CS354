////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
// Other Files:      intdate.c, sendsig.c
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


#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

//global counter counting the total number of division
int counter =  0;

/*Detecting the error of divided by 0 to stop the running program
 * sig: second of time
 */
void handler_SIGFPE(int sig){ 
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %d\n", counter);
    printf("The program will be terminated.\n");
    exit(0);
}


/*Detecting an interrupt signal to the running program
 * sig: second of time
 */
void handler_SIGINT(int sig){
    printf("\nTotal number of operations successfully completed: %d\n", counter);
    printf("The program will be terminated.\n");
    exit(0);
}


/*Calculate the quotient and remainder of doing the integer division operation, and record the total count of divisons has been completed
 * argc: total number of arguments
 * *argv[] pointer pointing to every argument
 */
int main(int argc, char *argv[]){
	struct sigaction actFpe;
	memset (&actFpe, 0, sizeof(actFpe));
	actFpe.sa_handler = handler_SIGFPE;

	struct sigaction actInt;
	memset (&actInt, 0, sizeof(actInt));
	actInt.sa_handler = handler_SIGINT;

        if(sigaction(SIGFPE,&actFpe,NULL) != 0){
	       	perror("Error in sigaction of SIGFPE.\n");
                exit(1);
        }
        if(sigaction(SIGINT,&actInt,NULL) != 0){
	       	perror("Error in sigaction of SIGINT.\n");
	       	exit(1);
	}


	while(1){
	       	int integer1 = 0;
	      	int integer2 = 0;

                char input1[100];
		char input2[100];

                printf("Enter first integer: ");
                if(fgets(input1, 100, stdin) == NULL){
			printf("Error in fgets().\n");
			exit(1);
		}
                integer1 = atoi(input1);

                printf("Enter second integer: ");
                if(fgets(input2, 100, stdin) == NULL){
			printf("Error in fgets().\n");
			exit(1);
		}
                integer2 = atoi(input2);

                int whole = integer1 / integer2;
                int r = integer1 % integer2;

                printf("%d / %d is %d with a remainder of %d\n", integer1, integer2, whole, r);
                counter++;
       }

}
