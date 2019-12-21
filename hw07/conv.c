#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 20

void 
ConvDecimal2Binary(int n)
{

	char buf[MAX_BUF];
	int i =0;
	
	// convert decimal number to binary number
	while(n>0){
		buf[i] = (n%2) ? '1' : '0';
		i++;
		n /= 2;
	}	
	// print binary format
	for(i--; i >=0 ; i--){
		printf("%c", buf[i]);
	}
	printf("\n");
}

void
main(int argc, char* argv[]){
	
	// check the number of arguments
	if( argc != 2){
		fprintf(stderr,"Usage: %s number \n", argv[0]);
		exit(1);
	}
	ConvDecimal2Binary(atoi(argv[1]));

}
