// Make my own cp program using file I/O system calls
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h> // for exit() function

#define	MAX_BUF	1024

void main(int argc, char *argv[])
{
	int 	fd1, fd2, count;
	char	buf[MAX_BUF];
	
	// if argc is not 3 , then print a error message
	if (argc != 3)  {
		printf("Usage: %s source destination\n", argv[0]);
		exit(1);
	}
	
	// int open(char *pathname ,int oflag(option)), read_only
	// open return -1 on error
	if ((fd1 = open(argv[1], O_RDONLY)) < 0)  {
		perror("open");
		exit(1);
	}
	
	// write_only, creat(so need mode of file), trunc(delete data in last file), 
	// 110100100 
	if ((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)  {
		perror("open");
		exit(1);
	}
	
	// read returns number of bytes, -1 on error
	while ( (count = read(fd1, buf, MAX_BUF)) > 0 ){
		write(fd2, buf, count);
	}

	close(fd1);
	close(fd2);
}
