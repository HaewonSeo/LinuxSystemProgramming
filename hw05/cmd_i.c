// Command-line processor : iteration version using one process
#include <stdio.h>
#include <unistd.h>
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

	while (1)  {
		printf("CMD> ");a
		// get a command through stdin 
		fgets(cmd, MAX_CMD, stdin);	
		if (cmd[0] == 'q')
			break;

		DoCmd(cmd);
	}
}
