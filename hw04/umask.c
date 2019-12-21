// Set file mode creation mask
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>// for exit()
#include <fcntl.h> // for creat()
void main()
{	
	// it sets the calling process's file mode creation mask to 0 & 0777
	// this system call always succeeds and the previous value of the mask is returned
	umask(0);
	// bar : -rw-rw-rw-
	// creat() returns -1 on error
	if (creat("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)  {
		perror("creat");
		exit(1);
	}
	
	// sets below cmasks to 0 
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	// foo : -rw-------
	if (creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)  {
		perror("creat");
		exit(1);
	}
}
