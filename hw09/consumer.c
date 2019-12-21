// Consumer process
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
	
	// get shm
	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	// attach the shm
	if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

	srand(0x9999); //set the seed

	for (i = 0 ; i < NLOOPS ; i++)  {
		if (pBuf->counter == 0)  {
			printf("Consumer: Buffer empty. Waiting.....\n");
			//busy waiting
			while (pBuf->counter == 0)
				;
		}

		printf("Consumer: Consuming an item.....\n");
		data = pBuf->buf[pBuf->out].data; // get the data from buffer
		pBuf->out = (pBuf->out + 1) % MAX_BUF; // update the out
		pBuf->counter--;

		usleep((rand()%100)*10000); //sleep in 0 ~ 1 sec
	}

	printf("Consumer: Consumed %d items.....\n", i);
	printf("Consumer: %d items in buffer.....\n", pBuf->counter);
}
