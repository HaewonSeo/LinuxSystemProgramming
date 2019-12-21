#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void
SigUsrHandler(int signo)
{	
	//SIGUSR1
	if (signo == SIGUSR1)  {
		printf("Received a SIGUSR1 signal\n");
	}
	//SIGUSR2
	else if (signo == SIGUSR2)  {
		printf("Received a SIGUSR2 signal\n");
	}
	else  {
		printf("Received unknown signal\n");
		printf("Terminate this process\n");
		exit(0);
	}
}

void
main()
{
	// register signal condition
	if (signal(SIGUSR1, SigUsrHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}

	if (signal(SIGUSR2, SigUsrHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}
	
	// 
	for ( ; ; )
		pause(); // this process is now waiting condition until any signal is arrived
}
