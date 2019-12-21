// Remove an empty directory
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
	// need 2 arguments
	if (argc != 2)  {
		fprintf(stderr, "Usage: %s dirname\n", argv[0]);
		exit(1);
	}
	
	// remove directory
	// redir() returns -1 on error 
	if (rmdir(argv[1]) < 0)  {
		perror("rmdir");
		exit(1);
	}
}
