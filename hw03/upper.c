#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUF 256

// change lower character to upper character and print that
void print_upper(FILE *fp ){
	
	char	buf[MAX_BUF];
	int 	i;
	// get string from fp
	while( fgets(buf, MAX_BUF, fp) ) {
		// lower character -> upper character
		for(i=0; i<MAX_BUF; i++){
			if( (buf[i] >= 97) && (buf[i] <= 122))
				buf[i] = buf[i] -32;
		}
		// print the buffer	
		printf("%s",buf);
	}

}

void main(int argc, char *argv[]){

	FILE	*src;
	
	// check the argc is 2
	if (argc != 2){
		fprintf(stderr, "Usage: %s source\n", argv[0]);
		exit(1);
	}
 	
	// open the file for read_text file
	if( ( src = fopen( argv[1], "rt")) == NULL ){
		perror("fpoen");
		exit(1);
	}
	
	print_upper(src);
	
	// close the file
	fclose(src);
}
