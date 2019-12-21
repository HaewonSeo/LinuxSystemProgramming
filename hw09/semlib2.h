#include <pthread.h>

typedef struct  {
	int		sval;	//semaphore value
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}
	sem_t;

int		sem_init(sem_t *sem, int pshared, int value); //make semaphore
int		sem_wait(sem_t *sem); //substract 1 , if 0, wait condition
int		sem_trywait(sem_t *sem); //not wait
int		sem_post(sem_t *sem); //signal, add 1
int		sem_getvalue(sem_t *sem, int *sval); //return semaphore value
int		sem_destroy(sem_t *sem); // destroy the semaphore
