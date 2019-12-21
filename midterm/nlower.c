#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void
PrintNlower(char *fname){
	
	FILE *fp;
	int ch;
	if( (fp = fopen(fname,"rt")) == NULL) {
		perror("fopen");
		exit(1);
	}

	int count =0;
	while((ch = fgetc(fp)) != EOF){
		if( (ch >= 97) && (ch <=122)) count++;
	}

	printf("%s : %d\n",fname, count);
	
	fclose(fp);
	pthread_exit(NULL);
}


void
main(int argc, char *argv[]){
	
	pthread_t tid[10];
	
	if (argc == 1)  {
		printf("Usage: %s  textfile ...\n ", argv[0]);
		exit(1);
	}

	int i;
	for(i=1;i<=argc-1;i++){
		if (pthread_create(&tid[i-1], NULL, (void *)PrintNlower, (void *)argv[i]) < 0)  {
			perror("pthread_create");
			exit(1);
		}
	}
	
	for(i=1;i<=argc-1;i++){
		pthread_join(tid[i-1],NULL);

	}
}
