// Change permissions of a file
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

void main()
{
	struct stat	statbuf;
	
	// get file status to statbuf	
	// stat() returns -1 on error
	if (stat("bar", &statbuf) < 0)  {
		perror("stat");
		exit(1);
	}

	// chmod() returns -1 on error
	// rw- rw- rw-  ->  rwS r-- rw-, set user id(04000)
	if (chmod("bar", (statbuf.st_mode & ~S_IWGRP) | S_ISUID) < 0)  {
		perror("chmod");
		exit(1);
	}
	
	// rw- --- ---  ->  rw- r-- r--
	if (chmod("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)  {
		perror("chmod");
		exit(1);
	}
}
