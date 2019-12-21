// thread1 : sum of 1 to 50
// thread2 : sum of 51 to 100
// get sum of thread1 and thread2

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int
Add(int input){  
	int i;
	int sum;
	sum=0;

	for(i=input; i<input+50; i++){
		sum = sum + i; 	
	}
	return sum;
	pthread_exit(NULL);
}

void
main()
{

	pthread_t tid1,tid2;
	int sum1, sum2;

	if(pthread_create(&tid1, NULL, (void *)Add, (void *)1) <0){
		perror("pthread_create");
		exit(1);
	}

	if(pthread_create(&tid2, NULL, (void *)Add, (void *)51) <0){
		perror("pthread_create");
		exit(1);
	}
	
	printf("Threads created, tid = %lu, %lu\n", tid1,tid2);

	if(pthread_join(tid1, &sum1) < 0){
		perror("pthread_join");
		exit(1);
	}
	
	if(pthread_join(tid2, &sum2) < 0){
		perror("pthread_join");
		exit(1);
	}

	printf("Threads terminated, tid = %lu, %lu\n", tid1,tid2);
	printf("sum of thread1 : %d, sum of thread2 : %d\n", sum1, sum2);
	printf("sum of thread1 and thread2 : %d\n" , sum1+sum2);

}

