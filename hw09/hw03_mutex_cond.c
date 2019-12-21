// hw03_mutex_condition variable in multi-thread environment
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include "shm.h"
#include <unistd.h>
#include <pthread.h>


//Global variable
char Msg[100];

pthread_t			tid1, tid2;
pthread_cond_t		Condition, Condition2;
pthread_mutex_t		Mutex;

void
Sipc1(void *dummy)
{	
	//lock(&mutex)
	if(pthread_mutex_lock(&Mutex) <0){
		fprintf(stderr,"mutex lock failure\n");
		exit(1);
	}
	//cond_wait(&condition,&mutex)
	if(pthread_cond_wait(&Condition, &Mutex) < 0){
		fprintf(stderr,"condition variable wait failure\n");
		exit(1);
	}

	printf("Received request: %s.....", Msg);
	sprintf(Msg, "This is a reply from tid1(%d).", tid1);
	printf("Replied.\n");

	//cond_signal(&condition2)
	if(pthread_cond_signal(&Condition2) < 0){
		fprintf(stderr,"condition variable signal failure\n");
		exit(1);
	}
	//unlock(&mutex)
	if(pthread_mutex_unlock(&Mutex) < 0 ){
		fprintf(stderr,"mutex unlock failure\n");
		exit(1);
	}
	//terminate thread
	pthread_exit(NULL);

}

void
Sipc2(void *dummy)
{
	//lock(&mutex) 
	if(pthread_mutex_lock(&Mutex) < 0){
		fprintf(stderr,"mutex lock failure\n");
		exit(1);
	}

	sprintf(Msg, "This is a request from tid2(%d).", tid2);
	printf("Sent a request.....");

	//cond_signal(&condition)
	if(pthread_cond_signal(&Condition)<0){
		fprintf(stderr,"condition variable signal failure\n");
		exit(1);
	}

	//cond_wait(&condition2,&mutex)
	if(pthread_cond_wait(&Condition2, &Mutex) < 0){
		fprintf(stderr,"condition variable wait failure\n");
		exit(1);
	}

	printf("Received reply: %s\n", Msg);
	
	//unlock(mutex)	
	if(pthread_mutex_unlock(&Mutex) < 0 ){
		fprintf(stderr,"mutex unlock failure\n");
		exit(1);
	}	
	
	pthread_exit(NULL);
}


void
main()
{
	// intialize the condition variables & mutex
	if (pthread_cond_init(&Condition, NULL) < 0)  {
		perror("pthread_cond_init");
		pthread_exit(NULL);
	}
	if (pthread_cond_init(&Condition2, NULL) < 0)  {
		perror("pthread_cond_init");
		pthread_exit(NULL);
	}
	if (pthread_mutex_init(&Mutex, NULL) < 0)  {
		perror("pthread_mutex_init");
		pthread_exit(NULL);
	}

	// create threads
	if (pthread_create(&tid2, NULL, (void *)Sipc2, (void *)NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_create(&tid1, NULL, (void *)Sipc1, (void *)NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	// wait for termination of thread
	if (pthread_join(tid1, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}
	if (pthread_join(tid2, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}
	
	sleep(1);
	// destroy condition variables & mutex
	if (pthread_cond_destroy(&Condition) < 0)  {
		perror("pthread_cond_destroy");
		pthread_exit(NULL);
	}
	if (pthread_cond_destroy(&Condition2) < 0)  {
		perror("pthread_cond_destroy");
		pthread_exit(NULL);
	}
	if (pthread_mutex_destroy(&Mutex) < 0)  {
		perror("pthread_mutex_destroy");
		pthread_exit(NULL);
	}	

}
