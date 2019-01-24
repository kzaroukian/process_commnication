#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>

// Process Communication for Lab 3
// By Kaylin Zaroukian and Marc Chesebro

void interuptHandler (int sigNum) 
{ 
	printf (" received an interrupt.\n"); 
	exit(0); 
}

void userSignalHandler(int sigNum){

	printf("user handler");
	if(sigNum == SIGUSR1){
		printf("received a SIGUSR1 signal\n");

	} else if(sigNum == SIGUSR2){
		printf("received a SIGUSR2 signal\n");
	}
}

int main() 
{ 
	//assinging the interupt handler - Ctrl-C
	signal (SIGINT,  interuptHandler); 

	pid_t childPid = fork();
	
	if(childPid == 0){
		//loop: sleep randomly send signals
		pid_t parentPid = getppid();
		while(1){
			int waitTime;
			waitTime = rand() % (6-1) +1;
			sleep(waitTime);
			int randSend = rand() % (2-0);
			if (randSend == 0) {
			   kill(parentPid, SIGUSR1);
			} else {
			   kill(parentPid, SIGUSR2);
			}
		}
	}else{
		//user signal handlers - These will be sent from the child using kill()
		signal(SIGUSR1, userSignalHandler);
		signal(SIGUSR2, userSignalHandler);
		
		while(1){
			printf ("waiting...\n"); 
			pause();
		}
	}	
	return 0; 
}


