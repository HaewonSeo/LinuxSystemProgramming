// Synchronization between parent and child using pipe
#include <stdio.h>
#include "synclib.h"
#include <stdlib.h>

#define	NLOOPS	5

void
main()
{
	int		i;
	pid_t	pid;
	
	// Initialization
	TELL_WAIT();
	
	// Pfd1 : parent -> child
	// Pfd2 : child -> parent 
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	// parent process
	else if (pid > 0)  {
		for (i = 0 ; i < NLOOPS ; i++)  {
			TELL_CHILD(); 
			printf("Parent: Tell to child\n");
			printf("Parent: Wait for child to tell\n");
			WAIT_CHILD(); //parent -> wait, then child start
		}
	}
	// child process
	else  {
		for (i = 0 ; i < NLOOPS ; i++)  {
			printf("Child: Wait for parent to tell\n");
			WAIT_PARENT();// child -> wait
			TELL_PARENT();
			printf("Child: Tell to parent\n");
		}
	}
}
