// Create a directory
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{	
	// need 2 arguments 
	if (argc != 2)  {
		fprintf(stderr, "Usage: %s dirname\n", argv[0]);
		exit(1);
	}
	
	// int mkdir(char *pathname, mode_t mode);
	// drwxr-xr-x
	if (mkdir(argv[1], 0755) < 0)  {
		perror("mkdir");
		exit(1);
	}
}
