// Make a new name for a file(symbolic link)
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
	// need 3 arguments
	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destinaion\n", argv[0]);
		exit(1);
	}
	
	// int symlin(char *actualpath, char *sympath);
	// symbolic link
	if (symlink(argv[1], argv[2]) < 0)  {
		perror("link");
		exit(1);
	}
}

//update it!!
//check
//adasdsad

//dasddddd
