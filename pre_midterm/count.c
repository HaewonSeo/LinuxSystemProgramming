#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 256

void
main(int argc, char *argv[]){

	FILE	*fp;
	char 	buf[MAX_BUF];
	int		count;

	if (argc != 2)  {
    	printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
 
	if ((fp = fopen(argv[1], "rt")) == NULL){
		perror("fopen");
		exit(1);
	}

	printf("====\n");

	count =0;	
	while( fscanf(fp,"%s",buf) != EOF ){
		count++;
	}


	printf("count : %d\n", count);
	
	fclose(fp);
}
