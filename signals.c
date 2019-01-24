#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>

void interuptHandler (int sigNum) 
{ 
	printf (" received an interrupt.\n"); 
	exit(0); 
}

void userSignalHandler(int sigNum){

	printf("user handler");
	if(sigNum == SIGUSR1){
		printf("received a SIGUSR1 signal");

	} else if(sigNum == SIGUSR2){
		printf("received a SIGUSR2 signal");
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
			sleep(1);
			kill(parentPid, SIGUSR1);
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


