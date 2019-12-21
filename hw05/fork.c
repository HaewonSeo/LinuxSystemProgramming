#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int		Var = 6;
char	Buf[] = "a write to stdout\n";

void
main()
{
	int		var;
	pid_t	pid;

	var = 88;
	write(STDOUT_FILENO, Buf, sizeof(Buf)-1);
	printf("Before fork\n");
	
	// check error
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	// now the number of process is two, state is ready 
	else if (pid == 0)  {
		/* child */
		Var++;
		var++;
	}
	// parent process waits 2 second
	else  {
		/* parent */
		sleep(2);
	}

	printf("pid = %d, Var = %d, var = %d\n", getpid(), Var, var);
	// wait 2 sec -> ready 
}
