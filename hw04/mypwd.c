// Get current working directory
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define	MAX_BUF	256

void main(int argc, char *argv[])
{
	char	buf[MAX_BUF];
	
	// getcwd() returns NULL on error 
	if (getcwd(buf, MAX_BUF) == NULL)  {
		perror("getcwd");
		exit(1);
	}
	// print current working directory
	printf("%s\n", buf);
}
