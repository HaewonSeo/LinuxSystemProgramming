// Execute a command string in a program
#include <stdio.h>
#include <stdlib.h>

void
main()
{
	int		status;
	
	// system() returns termination status of the shell if OK, -1 on error
	if ((status = system("date")) < 0)  {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);

	if ((status = system("nosuchcommand")) < 0)  {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);

	// exit 44 : returns status of 44
	if ((status = system("who ;exit 44")) < 0)  {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);
}
