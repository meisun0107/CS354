////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        intdate.c
// Other Files:      division.c, sendsig.c
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
#include<signal.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>

//global varibale of time period to alarm
int t = 3;
//global counter
int counter = 0;


/*a alarm clock for deliver of a signal and print the pid of the program and the current time 
 *sig: second of time
 */
void handler_SIGALRM(int sig){
	time_t currTime;
	if (time(&currTime) == -1) {
		perror("Error in time().\n");
		exit(1);
	}

	char *ptr = ctime(&currTime); 
	if (ptr == NULL) {
		printf("Error in ctime().\n");
		exit(1);
	}
	printf("PID: %d | Current Time: %s",getpid(),ptr);
        alarm(t);

}

/*Typing Control+c sends an interrupt signal to the running program
 * sig: second of time
 */
void handler_SIGINT(int sig){
	printf("\nSIGINT received.\n");
	printf("SIGUSR1 was received %d times. Exiting now.\n",counter);
	exit(0);
}

/*Catching SIGUSR1 and prints a message on receiving a SIGUSR1 signal.
 *sig: second of time
 */
void handler_SIGUSR1 (int sig) {
	printf("SIGUSR1 caught!\n");
	counter++;
}

/*The main function that call all the functions above to send, catch and terminate signals.
 * argc: total number of arguments
 * *argv[] pointer pointing to every argument
 */
int main (int argc, char *argv[]){
	printf("Pid and time will be printed every 3 seconds.\n");
	printf("Enter ^C to end the program.\n");

	struct sigaction act;
        memset (&act, 0, sizeof(act));
	act.sa_handler = handler_SIGALRM;

	struct sigaction actInt;
        memset (&actInt, 0, sizeof(actInt));
        actInt.sa_handler = handler_SIGINT;

	struct sigaction actUsr1;
        memset (&actUsr1, 0, sizeof(actUsr1));
        actUsr1.sa_handler = handler_SIGUSR1;

	alarm(t);


	if(sigaction(SIGALRM,&act,NULL) != 0){
		printf("Error in sigaction of SIGALRM\n");
		exit(1);
	}

	if(sigaction(SIGINT,&actInt,NULL) != 0){
		printf("Error in sigaction of SIGINT\n");
		exit(1);
	}

	if(sigaction(SIGUSR1,&actUsr1,NULL) != 0){
		printf("Error in sigaction of SIGUSR1\n");
		exit(1);
	}









	while(1){
	}
}
