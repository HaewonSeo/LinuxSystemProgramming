#include <stdio.h>
#include <stdlib.h>

void
main( int argc, char *argv[]){
	
	if (argc != 2)  {
		printf("Usage: %s number\n", argv[0]);
		exit(1);
	}

	int i;
	int n;
	n = atoi(argv[1]);
	int binary[20] = {0,};
	int pos = 0;

	while(1){
		binary[pos] = n%2;
		n= n/2;
		pos++;
		if(n==0)
			break;
	}
	
	for(i=pos-1; i>=0; i--){
		printf("%d", binary[i]);
	}
	printf("\n");

}

