#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void
main()
{
	pid_t	pid;
	int		status;
	
	// error check
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	//child
	else if (pid == 0)  {
		printf("I'm a child\n");
		sleep(2);
	}
	//parent
	else  {
		//wait until close the child process 
		wait(&status);
		printf("A child killed with %d status\n", status);
	}
}
