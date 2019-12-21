// Copy binary file by fread&fwrite
#include <stdio.h>
#include <stdlib.h>
#define	MAX_BUF	1024

void main(int argc, char *argv[])
{
	FILE	*src, *dst;
	char	buf[MAX_BUF];
	int		count;
	
	// if argc != 3, print error message
	// standard error stream	
	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}
	
	// open file for read_binary file
	// print error message
	if ((src = fopen(argv[1], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	
	// open file for write_binary file
	if ((dst = fopen(argv[2], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	
	// fread(fwrite) returns number of objects read(written) if Ok, EOF 0n error
	while ( fread(buf, 1, MAX_BUF, src) > 0)  {
		fwrite(buf, 1, count, dst);
	}
	
	// close the files
	fclose(src);
	fclose(dst);
}
