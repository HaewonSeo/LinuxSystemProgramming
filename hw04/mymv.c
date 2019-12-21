// Rename a file or directory
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
	// need 3 arguments 
	if (argc != 3)  {
		fprintf(stderr, "Usage: %s old new\n", argv[0]);
		exit(1);
	}
	
	// rename() renames a file, moving it between directories if required.
	if (rename(argv[1], argv[2]) < 0)  {
		perror("rename");
		exit(1);
	}
}
