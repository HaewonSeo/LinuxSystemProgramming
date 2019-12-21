// Make a big-hole file using creat&lseek system call
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void main()
{
	int 	fd;
	char	ch = '\0'; // string terminator

	// int  creat(char *pathname, mode_t mode), In mode, first 0 means octal-decimal, so 100000000
	if ((fd = creat("file.hole", 0400)) < 0)  {
		perror("creat"); // print error message 
		exit(1); // exit in error
	}

	// int lseek(int fd, off_t offset, int whence), SEEK_SET means ahead of file.
	// lseek returns new file offset if OK, -1 on error
	if (lseek(fd, 1023, SEEK_SET) < 0)  {
		perror("lseek"); // print error message
		exit(1); // exit in error
	}
	
	// ssize_t write(int fd, void *buf, size_t nbytes)
	write(fd, &ch, 1);

	close(fd);
}
