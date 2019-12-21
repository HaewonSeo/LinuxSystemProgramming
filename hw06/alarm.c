#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static unsigned int	AlarmSecs;


void
SigAlarmHandler(int signo)
{
	// re register signal handler
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}
	
	// set a alarm()
	alarm(AlarmSecs);

	/* Do something */
	printf("."); // buffuring until input the '\' 
	fflush(stdout); // write the buffer cache to disk immediately, stdout is console(not disk)

	return;
}

int
SetPeriodicAlarm(unsigned int nsecs)
{	
	// register a signal handler.
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
		return -1;
	}

	AlarmSecs = nsecs;

	alarm(nsecs);

	return 0;
}

void
main()
{
	printf("Doing something every one seconds\n");

	SetPeriodicAlarm(1);
	
	// wait for signal
	for ( ; ; )
		pause();
}
