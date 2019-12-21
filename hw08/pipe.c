#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define	MAX_BUF	128

void
main()
{
	int		n,m, fd[2],fd2[2];
	pid_t	pid;
	char	buf[MAX_BUF], buf2[MAX_BUF];

	// create pipe1
	if (pipe(fd) < 0)  {
		perror("pipe1");
		exit(1);
	}
	// homework 2 : add pipe for sending message from child to parent
	// create pipe2
	if (pipe(fd2) < 0)  {
		perror("pipe2");
		exit(1);
	}
	// make child process
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}

	// pipe1 : parent -> child
	// pipe2 : child -> parent

	// child process
	else if (pid == 0)  {
		//read from pipe1
		close(fd[1]); // close the write of pipe1
		printf("Child : Wait for parent to send data\n");
		//wait for parent to send data
		if ((n = read(fd[0], buf, MAX_BUF)) < 0)  {
			perror("read1");
			exit(1);
		}
		printf("Child : Received data from parent: ");
		fflush(stdout); // for not terminated to \n string, use fflush()
		write(STDOUT_FILENO, buf, n);
		
		//write to pipe2
		close(fd2[0]); // close the read of pipe2
		strcpy(buf2, "Message[Child to Parent]\n");
		printf("Child : Send data to parent\n"); 
		write(fd2[1], buf2, strlen(buf2)+1); // '+1" because of null termination 
		
	}
	// parent process
	else  {
		//write to pipe1
		close(fd[0]); // close the read of pipe1
		strcpy(buf, "Hello, World!\n");
		printf("Parent: Send data to child\n");
		write(fd[1], buf, strlen(buf)+1);

		//read from pipe2
		close(fd2[1]);	// close the write of pipe2
		printf("Parent : Wait for child to send data\n");
		//wait for child to send data
		if ((m = read(fd2[0], buf2, MAX_BUF)) < 0 ) {
			perror("read2");
			exit(1);
		}
		printf("Parent : Received data from child: ");
		fflush(stdout);
		write(STDOUT_FILENO, buf2, m);
	}

	exit(0);
}
