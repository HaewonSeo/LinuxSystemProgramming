// Compile 3 case
// Anyway mainthread handles signals.
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


//#define	THREAD_MAIN
//#define	THREAD_1
#define	THREAD_2


void
SigIntHandler(int signo)
{
	// pthread_self() returns its thread id
	printf("Received a SIGINT signal by thread %d\n", pthread_self());
	printf("Terminate this process\n");

	exit(0);
}
//thread1 register signal handler
void
Thread1(void *dummy)
{
#ifdef	THREAD_1
	signal(SIGINT, SigIntHandler);
#endif

	while (1)
		;
}

//thread2 register signal handler
void
Thread2(void *dummy)
{
#ifdef	THREAD_2
	signal(SIGINT, SigIntHandler);
#endif

	while (1)
		;
}

void
main()
{
	pthread_t	tid1, tid2;
	
	// create thread1, thread2
	if (pthread_create(&tid1, NULL, (void *)Thread1, NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}
	if (pthread_create(&tid2, NULL, (void *)Thread2, NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}
	printf("Create two threads: tid1=%d, tid2=%d\n", tid1, tid2);
	printf("Main thread: tid=%d\n", pthread_self());

// we want know who is deal with the signal handler

// main thread register signal handler
#ifdef	THREAD_MAIN
	signal(SIGINT, SigIntHandler);
#endif

	printf("Press ^C to quit\n ");

	for ( ; ; )
		pause();
}
