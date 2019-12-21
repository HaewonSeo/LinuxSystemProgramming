#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "shm.h"
#include <unistd.h>


void
main()
{
	int		shmid;
	char	*ptr, *pData;
	int		*pInt;

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

	//busy waiting(actually block waiting is better, this will handle in semaphore part)
	//doing loop until time quantum is closed (40~60ms)
	//all shm datas are initalized to 0
	pInt = (int *)ptr;
	while ((*pInt) == 0)
		;

	pData = ptr + sizeof(int);
	printf("Received request: %s.....", pData);
	sprintf(pData, "This is a reply from %d.", getpid());
	*pInt = 0; // set the *pInt ro 0
	printf("Replied.\n");

	sleep(1);
	
	//remove the shm from system 
	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
}
