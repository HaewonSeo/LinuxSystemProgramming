// Producer & Consumer sharing bounded buffer (multi-threads version)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "prodcons.h"

BoundedBufferType	Buf;

// thread sleep in microsec
void
ThreadUsleep(int usecs)
{
	pthread_cond_t		cond;
	pthread_mutex_t		mutex;
	struct timespec		ts;
	struct timeval		tv;

	if (pthread_cond_init(&cond, NULL) < 0)  {
		perror("pthread_cond_init");
		pthread_exit(NULL);
	}
	if (pthread_mutex_init(&mutex, NULL) < 0)  {
		perror("pthread_mutex_init");
		pthread_exit(NULL);
	}

	gettimeofday(&tv, NULL);
	ts.tv_sec = tv.tv_sec + usecs/1000000;
	ts.tv_nsec = (tv.tv_usec + (usecs%1000000)) * 1000;
	if (ts.tv_nsec >= 1000000000)  {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}

	if (pthread_mutex_lock(&mutex) < 0)  {
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}
	if (pthread_cond_timedwait(&cond, &mutex, &ts) < 0)  {
		perror("pthread_cond_timedwait");
		pthread_exit(NULL);
	}

	if (pthread_cond_destroy(&cond) < 0)  {
		perror("pthread_cond_destroy");
		pthread_exit(NULL);
	}
	if (pthread_mutex_destroy(&mutex) < 0)  {
		perror("pthread_mutex_destroy");
		pthread_exit(NULL);
	}
}

void
Producer(void *dummy)
{
	int		i, data;

	printf("Producer: Start.....\n");

	for (i = 0 ; i < NLOOPS ; i++)  {
		// When buffer is full
		if (Buf.counter == MAX_BUF)  {
			printf("Producer: Buffer full. Waiting.....\n");
			//Busy waiting
			while (Buf.counter == MAX_BUF)
				;
		}

		printf("Producer: Producing an item.....\n");
		data = (rand()%100)*10000; //make data
		Buf.buf[Buf.in].data = data;//put data in buffer 
		Buf.in = (Buf.in + 1) % MAX_BUF; // update the in 
		Buf.counter++; 

		ThreadUsleep(data);
	}

	printf("Producer: Produced %d items.....\n", i);
	printf("Producer: %d items in buffer.....\n", Buf.counter);
	
	//terminate the thread
	pthread_exit(NULL);
}

void
Consumer(void *dummy)
{
	int		i, data;

	printf("Consumer: Start.....\n");

	for (i = 0 ; i < NLOOPS ; i++)  {
		// When buffer is empty
		if (Buf.counter == 0)  {
			printf("Consumer: Buffer empty. Waiting.....\n");
			//Busy waiting
			while (Buf.counter == 0)
				;
		}

		printf("Consumer: Consuming an item.....\n");
		data = Buf.buf[Buf.out].data; // get dat from buffer
		Buf.out = (Buf.out + 1) % MAX_BUF; // update the out
		Buf.counter--;

		ThreadUsleep((rand()%100)*10000);
	}

	printf("Consumer: Consumed %d items.....\n", i);
	printf("Consumer: %d items in buffer.....\n", Buf.counter);
	
	// terminate the thread 
	pthread_exit(NULL);
}

void
main()
{
	pthread_t	tid1, tid2;

	srand(0x8888);	// set the seed

	// create Producer thread 
	if (pthread_create(&tid1, NULL, (void *)Producer, (void *)NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	// create Consumer thread
	if (pthread_create(&tid2, NULL, (void *)Consumer, (void *)NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	// Wait for termination of Producer thread 
	if (pthread_join(tid1, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}
	// Wait for termination of Consumer thread
	if (pthread_join(tid2, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}

	printf("Main    : %d items in buffer.....\n", Buf.counter);
}