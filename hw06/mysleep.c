// Make my own sleep system call using signal&pause&alarm  system call
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void
SigAlarmHandler(int signo)
{	
	// for preventing terimination of the process
	/* nothing to do, just return to wake up the pause */
	return;
}

unsigned int
mysleep(unsigned int nsecs)
{	
	// register a signal handler
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
		return nsecs;
	}
	// after nsecs, SIGARLM is come
	alarm(nsecs);

	pause(); // wait until arrive the any signal, we want SIGALRM

	return alarm(0); //if, other signal is come(at 3sec), then return remaining 2sec 
	// return the difference time(remained time(2sec))  
}

void
main()
{
	printf("Wait for 5 seconds...\n");

	mysleep(5);
}
