// calling a non-reentrant function from signal handler
#include <stdio.h>
#include <signal.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void
MyAlarmHandler(int signo)
{
	struct passwd	*rootptr;
	
	// re register signal handler
	signal(SIGALRM, MyAlarmHandler);
	// send SIGALRM after 1 second
	alarm(1);

	printf("in signal handler\n");
	// get struct passwd of root
	if ((rootptr = getpwnam("root")) == NULL)  {
		perror("getpwnam");
		exit(1);
	}

	return;
}

void
main()
{
	struct passwd	*ptr;
	
	// register signal handler
	signal(SIGALRM, MyAlarmHandler);
	alarm(1);

	for ( ; ; )  {
		// return struct passwd of argument.
		if ((ptr = getpwnam("lsp24")) == NULL)  {
			perror("getpwnam");
			exit(1);
		}
		
		// if ptr gets struct passwd of "root" in MyAlarmHandler(),
		// then, print error message and exit.
		if (strcmp(ptr->pw_name, "lsp24") != 0)  {
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
			exit(0);
		}
	}
}
