// creat a new process
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void
main()
{
	int		pid;
	
	// fork() returns -1 on error
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	// returns 0 in child
	else if (pid == 0)  {
		/* child */
		printf("I am %d. My parent is %d.\n", getpid(), getppid());
	}
	// returns process ID of child in parent
	else  {
		/* parent */
		printf("I am %d. My child is %d.\n", getpid(), pid);
	}
}
