#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define	ARRAY_SIZE	40000
#define	MALLOC_SIZE	100000
#define	SHM_SIZE	100000
#define	SHM_MODE	(SHM_R | SHM_W)

//global variance
char	Array[ARRAY_SIZE];

void
main()
{
	int		shmid;
	char	*ptr, *shmptr;

	//dynamic memory allocation
	if ((ptr = (char *)malloc(MALLOC_SIZE)) == NULL)  {
		perror("malloc");
		exit(1);
	}
	
	// obtain a shared memory ID
	// shmid -> fd3 in fd table
	// IPC_PRIVATE : just for this process, when process died, then shm removed automically,
	//				In this situation, this is safe method than using key  
	if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	// attatch a shared memory segment to the process' address space
	if ((shmptr = shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

	printf("Array[] from %p to %p\n", &Array[0], &Array[ARRAY_SIZE]);//Global var -> data segment
	printf("Stack around %p\n", &shmid); //stack
	printf("Malloced from %p to %p\n", ptr, ptr+MALLOC_SIZE);// heap
	printf("Shared memory attached from %p to %p\n", shmptr, shmptr+SHM_SIZE); //shared memory
	
	//remove the shared memory segment from the system 
	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
}
