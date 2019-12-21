// Command-line processor : a thread per command
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define	MAX_CMD		256

void
DoCmd(char *cmd)
{
	printf("Doing %s", cmd);
	sleep(1);
	printf("Done\n");
	
	//terminate a thread
	pthread_exit(NULL);
}

void
main()
{
	char		cmd[MAX_CMD];
	pthread_t	tid;

	while (1)  {
		printf("CMD> ");
		// get command through stdin
		fgets(cmd, MAX_CMD, stdin);

		// if command starts to "q", then break while()	
		if (cmd[0] == 'q')
			break;
		// create a thread
		if (pthread_create(&tid, NULL, (void *)DoCmd, (void *)cmd) < 0)  {
			perror("pthread_create");
			exit(1);
		}

//#if 0	
		// wait for termination of thread.
		pthread_join(tid, NULL);
//#endif
	}
}
