// Producer & Consumer sharing bounded buffer(multi-process version)
// Producer process
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "prodcons.h"

void 
main()
{
	BoundedBufferType	*pBuf;
	int					shmid, i, data;

	// get shared memory
	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	// attach the shared memory 
	if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

	srand(0x8888); //set the seed

	for (i = 0 ; i < NLOOPS ; i++)  {
		if (pBuf->counter == MAX_BUF)  {
			printf("Producer: Buffer full. Waiting.....\n");
			//busy waiting 
			while (pBuf->counter == MAX_BUF)
				;
		}

		printf("Producer: Producing an item.....\n");
		data = (rand()%100)*10000;  // make the data ramdomly
		pBuf->buf[pBuf->in].data = data; // put data into buffer
		pBuf->in = (pBuf->in + 1) % MAX_BUF; // update the in
		pBuf->counter++;

		usleep(data); // sleep in 0 ~ 1000000 microsec
	}

	printf("Producer: Produced %d items.....\n", i);

	sleep(2);
	printf("Producer: %d items in buffer.....\n", pBuf->counter);
	
	// remove the shared memory 	
	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
}
