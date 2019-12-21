// Command-line processor : a process per command
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define	MAX_CMD		256

void
DoCmd(char *cmd)
{
	printf("Doing %s", cmd);
	sleep(1);
	printf("Done\n");
}

void
main()
{
	char	cmd[MAX_CMD];
	int		pid;

	while (1)  {
		printf("CMD> ");
		// get a command through stdin
		fgets(cmd, MAX_CMD, stdin);	
		if (cmd[0] == 'q')
			break;
		
		// creat a new process
		if ((pid = fork()) < 0)  {
			perror("fork");
			exit(1);
		}
		// child process
		else if (pid == 0)  {
			DoCmd(cmd);
			exit(0);
		}
// wait until child process is terminated
//#if 0
		else  {
			wait(NULL);
		}
//#endif
	}
}
