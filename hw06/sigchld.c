// Use SIGCHLD for waiting termination of child process asynchronous.
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


void
SigChildHandler(int signo){
	printf("child process is terminated..\n ");
}

void
main(){

	pid_t	pid;
	
	// register signal handler
	signal(SIGCHLD, SigChildHandler);
	
	// create process
	if ((pid = fork()) < 0 ){
		perror("fork");
		exit(1);
	}
	// child process terimated after 2 seconds, and send SIGCHLD to parent process.
	else if( pid == 0) {
		printf("I'm child process\n");
		sleep(2);
	}
	else {
		//Do Something
		while(1);
	}

}
