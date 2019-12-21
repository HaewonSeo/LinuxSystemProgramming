#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"
#include <stdlib.h>
#include <unistd.h>

void
main()
{
	int		shmid;
	char	*ptr, *pData;
	int		*pInt;

	// obtaion a shm identifier 
	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	// attach the shm that is same in sipc1.c process to process's address space
	if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}
	
	pInt = (int *)ptr; //pInt : first 4 bytes in shm
	pData = ptr + sizeof(int); // pData : next pInt 
	sprintf(pData, "This is a request from %d.", getpid());
	*pInt = 1; // set the *pInt to 1
	printf("Sent a request.....");

	//busy waiting
	while ((*pInt) == 1)
		;

	printf("Received reply: %s\n", pData);
}
