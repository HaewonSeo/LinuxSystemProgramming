#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 10

void 
CountNlower(char *file)
{
	
	int n =0;
	int ch;
	FILE *fp;

	// check file open error
	if( (fp = fopen(file, "rt")) == NULL){
		perror("file open");
		exit(1);	
	}
	
	// count the number of lower characters
	while((ch = fgetc(fp)) != EOF) {
		if( islower(ch))
			n++;
	}
	// close fp
	fclose(fp);
	
	// print the number of lower characters
	printf("%s : %d\n", file, n);
	// terminate a thread
	pthread_exit(NULL);
}


void
main(int argc, char *argv[])
{
	int i;
	pthread_t tid[MAX];
	
	if (argc == 1){
		printf("Usage: %s textfile ...\n", argv[0]);
		exit(1);
	}

	// creat threads 
	for(i =0; i <(argc-1); i++){
		if( pthread_create(&tid[i],NULL, (void*)CountNlower, argv[i+1]) <0){
			perror("pthread_create");
			exit(1);
		}
	}

	// wait for termination of other threads
	for(i =0; i <(argc-1); i++){
		pthread_join(tid[i],NULL);
	}



}
