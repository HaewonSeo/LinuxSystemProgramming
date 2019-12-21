// IPC between parent and child using memory mapped file of /dev/zero

#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "synclib.h"
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define	NLOOPS	10
#define	SIZE	sizeof(long)
//64-bit linux -> long is 8byte ( $getconf LONG_BIT )

 
int
update(long *ptr)
{
	return ((*ptr)++);
}

void
main()
{
	int		fd, i, counter;
	int		shmid;
	long 	*area;
	pid_t	pid;
	//caddr_t	area;
	
	/* --- original file ---

	// make shared memory, unix/linux form 
	if ((fd = open("/dev/zero", O_RDWR)) < 0)  {
		perror("open");
		exit(1);
	}
	if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))
		== (caddr_t) -1)  {
		perror("mmap");
		exit(1);
	}
	close(fd);
	*/

	// --- homework part ---
	
	if ((shmid = shmget(IPC_PRIVATE, SIZE, (SHM_R | SHM_W) )) < 0) {
		perror("shmget");
		exit(1);
	}
	if ((area = shmat(shmid, 0, 0)) == (void *) -1) {
		perror("shmat");
		exit(1);
	}
	

	// make two pipes 
	TELL_WAIT();
	//fork 
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	//parent process
	// area : shm
	else if (pid > 0)  {
		for (i = 0 ; i < NLOOPS ; i += 2)  {
			if ((counter = update((long *) area)) != i)  {
				fprintf(stderr, "Counter mismatch\n");
				exit(1);
			}
			printf("Parent: counter=%d\n", counter);
			TELL_CHILD();
			WAIT_CHILD();
		}
	}
	//child process
	else  {
		for (i = 1 ; i < NLOOPS ; i += 2)  {
			WAIT_PARENT();
			if ((counter = update((long *) area)) != i)  {
				fprintf(stderr, "Counter mismatch\n");
				exit(1);
			}
			printf("Child : counter=%d\n", counter);
			TELL_PARENT();
		}
	}
	

	// remove the shared memory segment from the system 
	// When set the key to IPC_PRIVATE, if close the shell then shmid removed
	if (shmctl(shmid, IPC_RMID, 0) < 0) {
		perror("shmctl");
		exit(1);
	}


}


