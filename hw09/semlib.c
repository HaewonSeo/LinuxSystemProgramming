#include <stdio.h>
#include "semlib.h"
 
 
int
semInit(key_t key)
{
    int     semid;
	// obtain a semaphore set ID
    if ((semid = semget(key, 1, 0600 | IPC_CREAT)) < 0)  {
		perror("semget");
        return -1;
    }

    return semid;
}
 
int
semInitValue(int semid, int value)
{
    union semun {
            int     val;
    } semun;

    semun.val = value;
	// set the semaphore value
    if (semctl(semid, 0, SETVAL, semun) < 0)  {
		perror("semctl");
        return -1;
    }
 
    return semid;
}
 
int
semWait(int semid)
{
    struct sembuf   semcmd;
 
    semcmd.sem_num = 0;	// member # in set 
    semcmd.sem_op = -1; // operation
    semcmd.sem_flg = SEM_UNDO; // for unnormally termination 
	// semaphore operations
    if (semop(semid, &semcmd, 1) < 0)  {
		perror("semop");
        return -1;
    }
 
    return 0;
}
 
int
semTryWait(int semid)
{
    struct sembuf   semcmd;
 
    semcmd.sem_num = 0;
    semcmd.sem_op = -1;
    semcmd.sem_flg = IPC_NOWAIT | SEM_UNDO; //set the flag to IPC_NOWAIT
    if (semop(semid, &semcmd, 1) < 0)  {
		perror("semop");
        return -1;
    }
 
    return 0;
}

int
semPost(int semid)
{
    struct sembuf   semcmd;
 
    semcmd.sem_num = 0;
    semcmd.sem_op = 1;
    semcmd.sem_flg = SEM_UNDO;
    if (semop(semid, &semcmd, 1) < 0)  {
		perror("semop");
        return -1;
    }
 
    return 0;
}

int
semGetValue(int semid)
{
    union semun {
            int     val;
    } dummy;
 
    return semctl(semid, 0, GETVAL, dummy);
}
 
int
semDestroy(int semid)
{
    union semun {
            int     val;
    } dummy;
 	// remove the semaphore set from the system
    if (semctl(semid, 0, IPC_RMID, dummy) < 0)  {
		perror("semctl");
        return -1;
    }
    close(semid);
 
    return 0;
}
