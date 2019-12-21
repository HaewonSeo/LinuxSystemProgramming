// Make a new name for a file (hard link)
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
	
	// int link(char *existingpath, char *newpath);
	// hard link
	if (link(argv[1], argv[2]) < 0)  {
		perror("link");
		exit(1);
	}
}

//update it!
//check 
//dd
//dddd

