#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void
SigIntHandler(int signo)
{
	printf("\nReceived a SIGINT signal\n");
	printf("Terminate this process\n");

	exit(0);
}

void
main()
{	
	//register a signal handler
	signal(SIGINT, SigIntHandler);

	printf("Press ^C to quit\n");

	// wait for signal
	for ( ; ; )
		pause();
}
