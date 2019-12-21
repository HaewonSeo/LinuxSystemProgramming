//Remove a file or direcory
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
	int		i;
	
	// it needs 2 argument at least
	if (argc == 1)  {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(1);
	}
	
	// remove() returns -1 on error 
	for (i = 1 ; i < argc ; i++)  {
		if (remove(argv[i]) < 0)  {
			perror("remove");
			exit(1);
		}
	}
}
