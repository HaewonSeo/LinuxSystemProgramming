#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 10

// use global variable for signal handler
static char *Argv[MAX];


void
AlarmHandler(int signo)
{	
	int pid;
	// make a child process
	if( (pid = fork()) < 0 ){
		perror("fork");
		exit(1);
	}
	// child process
	else if( pid == 0){
		execvp(Argv[0], Argv);
	}
	//parent process
	else{
		wait(NULL);
		exit(0);
	}
}

void
main(int argc, char *argv[])
{
	int i;
	
	//register signal handler 
	signal(SIGALRM, AlarmHandler);
	alarm(atoi(argv[1]));
	
	// copy argv to global variable Argv
	Argv[0] = "banner";
	for(i = 2; argv[i] != NULL; i++){
		Argv[i-1] =  argv[i];
	}
	Argv[i-1] = argv[i]; // for last NULL
	

	while(1)
		pause();


}
