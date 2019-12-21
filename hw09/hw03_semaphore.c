// hw03_semaphore
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "shm.h"
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

char Msg[100];

pthread_t	Tid1, Tid2;
sem_t			Semid, Semid2;
	
void
Sipc1(void *dummy)
{	

	printf("Wait request...\n");

	// wait request from Sipc2
	if( sem_wait(&Semid) < 0 ) {
		fprintf(stderr, "sem_wait failure\n");
		exit(1);
	}

	printf("Received request: %s.....", Msg);
	sprintf(Msg, "This is a reply from tid1(%d).", Tid1);
	printf("Replied.\n");

	// post(Semid2)
	if( sem_post(&Semid2) < 0) {
		fprintf(stderr, "sem_post failure\n");
		exit(1);
	}
	
	//terminate thread
	pthread_exit(NULL);

}

void
Sipc2(void *dummy)
{	

	sprintf(Msg, "This is a request from tid2(%d).", Tid2);
	printf("Sent a request.....");
	
	//post(Semid)
	if( sem_post(&Semid) < 0 ) {
		fprintf(stderr, "sem_post failure\n");
		exit(1);
	}
	
	//wait(Semid2)
	if( sem_wait(&Semid2) < 0 ) {
		fprintf(stderr, "sem_wait failure\n");
		exit(1);
	}	

	printf("Received reply: %s\n", Msg);
	
	//terminate thread
	pthread_exit(NULL);
}


void
main()
{
    //Initialize the semaphore, default value is 0 
    if( (sem_init(&Semid,0,0)) < 0){
       fprintf(stderr, "semInit failure\n");
       exit(1);
    }
     
    if( (sem_init(&Semid2,0,0)) < 0){
       fprintf(stderr, "semInit failure\n");
       exit(1);
    }

	// create threads
	if (pthread_create(&Tid1, NULL, (void *)Sipc1, (void *)NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_create(&Tid2, NULL, (void *)Sipc2, (void *)NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	// wait for termination of thread
	if (pthread_join(Tid1, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}
	if (pthread_join(Tid2, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}
	
	sleep(1);
	
	//remove the semaphore
	if (sem_destroy(&Semid) < 0){
		fprintf(stderr, "sem_destroy failure\n");
		exit(1);
	}
	if (sem_destroy(&Semid2) < 0){
		fprintf(stderr, "sem_destroy failure\n");
		exit(1);
	}
	
}
