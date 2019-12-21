//hw02_sipc2
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"
#include "semlib.h"
#include <stdlib.h>
#include <unistd.h>

void
main()
{
	int		shmid, semid,semid2;
	char	*ptr, *pData;

	// obtain a shm identifier 
	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	// attach the shm that is same in sipc1.c process to process's address space
	if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}
	// Initialize the semaphore, default value is 0
	if ((semid = semInit(SEM_KEY)) < 0) {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	if ((semid2 = semInit(SEM2_KEY)) < 0) {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	
	pData = ptr; 
	sprintf(pData, "This is a request from %d.....", getpid());	
	printf("Sent a request.....\n");

	//post(semid)
	if( semPost(semid) < 0) {
		fprintf(stderr, "semPost failure\n");
		exit(1);
	}
	
	//wait(semid2)
	if( semWait(semid2) <0) {
		fprintf(stderr, "semWait failure\n");
		exit(1);
	}
	
	printf("Received reply: %s\n", pData);
}

