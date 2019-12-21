#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void
SigAlarmHandler(int signo)
{
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}


	return;
}


void
main(int argc, char *argv[])
{
	signal(SIGALRM, SigAlarmHandler);


	//if (argc != 2)  {
	//		fprintf(stderr, "Usage: %s time string \n", argv[0]);
	//		exit(1);
	//}	
	
	while(1){
		alarm( atoi(argv[1]) );
		pause();
		char	*a[] = { "banner", argv[2], NULL};
		/* Do something */
		if( execvp("banner", a)<0){
			perror("execvp");
			exit(1);
		}
		
	}
}
