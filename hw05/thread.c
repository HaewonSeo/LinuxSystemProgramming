// Create & Terminate & Wait threads.
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


void
PrintMsg(char *msg)
{
	printf("%s\n", msg);
	
	// terminate the thread
	pthread_exit(NULL);
}

void
main()
{	
	// pthread_t is unsigned long
	pthread_t	tid1, tid2;
	char		*msg1 = "Hello, ";
	char		*msg2 = "World!\n";

	// create a thread
	// pthread_create(*tid, *attr, start_routine, *arg ) 
	if (pthread_create(&tid1, NULL, (void *)PrintMsg, (void *)msg1) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_create(&tid2, NULL, (void *)PrintMsg, (void *)msg2) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	printf("Threads created: tid=%lu, %lu\n", tid1, tid2);
	
	// wait for termination of another thread
	if (pthread_join(tid1, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}
	if (pthread_join(tid2, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}

	printf("Threads terminated: tid=%lu, %lu\n", tid1, tid2);
}
