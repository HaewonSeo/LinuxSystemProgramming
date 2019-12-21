//hw02_sipc1
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "shm.h"
#include <unistd.h>
#include "semlib.h"


void
main()
{
	int		shmid, semid, semid2;
	char	*ptr, *pData;

 	//obtain a shm  identifier
	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	//attatch the shm to process' address space
	if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

	//Initialize the semaphore, default value is 0 
	if( (semid = semInit(SEM_KEY)) < 0){
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	if( (semid2 = semInit(SEM2_KEY)) < 0){
		fprintf(stderr, "semInit failure\n");
		exit(1);
		}


	printf("Wait request...\n");

	//wait the request from hw02_sipc2
	if( semWait(semid) < 0 ) {
		fprintf(stderr, "semWait failure\n");
		exit(1);
	}


	pData = ptr;
	printf("Received request: %s.....\n", pData);
	sprintf(pData, "This is a reply from %d.", getpid());
	printf("Replied.\n");
	
	//post(semid2)
	if( semPost(semid2) < 0 ) {
		fprintf(stderr, "semPost failure\n");
		exit(1);
	}

	sleep(1);
	
	//remove the shm from system 
	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
	//remove the semaphore 
	if (semDestroy(semid) <0){
		fprintf(stderr, "semDestroy failure\n");
		exit(1);
	}

	if (semDestroy(semid2) <0){
		fprintf(stderr, "semDestroy failure\n");
		exit(1);
	}
}
