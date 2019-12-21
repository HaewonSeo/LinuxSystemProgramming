#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>

pthread_t	ThreadId[2];

void
SigIntHandler(int signo)
{
	int		i;

	printf("Received a SIGINT signal by thread %d\n", pthread_self());
	printf("Terminate other threads: tid=%d, %d\n", ThreadId[0], ThreadId[1]);

	// send cancellation request to two threads
	// returns 0 if OK, nonzero on error
	for (i = 0 ; i < 2 ; i++)  {
		if (pthread_cancel(ThreadId[i]))  {
			perror("pthread_cancel");
			exit(1);
		}
	}
	// wait for termaination of two threads
	// returns 0 if OK, nonzero on error
	for (i = 0 ; i < 2 ; i++)  {
		if (pthread_join(ThreadId[i], NULL))  {
			perror("pthread_join");
			exit(1);
		}
	}
	printf("Threads terminated: tid=%d, %d\n", ThreadId[0], ThreadId[1]);

	exit(0);
}

void
Thread1(void *dummy)
{
	printf("Thread %d created.....\n", pthread_self());
	
	// set the type and state of cancellation request
	// returns 0 if OK, non-zero on error
	// PTHREAD_CANCEL_ENABLE : default, when SIGTERM is arrived, then cancel the thread
	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL))  {
		perror("pthread_setcancelstate");
		// on error, terminate a thread.
		pthread_exit(NULL);
	}
	// PTHREAD_CANCEL_ASYNCHRONOUS : default, when SIGTERM is arrived, then cancel immediately
	if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL))  {
		perror("pthread_setcanceltype");
		pthread_exit(NULL);
	}

	while (1)
		;
}

void
Thread2(void *dummy)
{
	printf("Thread %d created.....\n", pthread_self());

	// set the type and state of cancellation request
	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL))  {
		perror("pthread_setcancelstate");
		pthread_exit(NULL);
	}
	if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL))  {
		perror("pthread_setcanceltype");
		pthread_exit(NULL);
	}

	while (1)
		;
}

void
main()
{
	// creat two threads
	if (pthread_create(&ThreadId[0], NULL, (void *)Thread1, NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}
	if (pthread_create(&ThreadId[1], NULL, (void *)Thread2, NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}
	
	// register a signal handler
	signal(SIGINT, SigIntHandler);

	printf("Press ^C to quit\n");

	for ( ; ; )
		pause();
}
