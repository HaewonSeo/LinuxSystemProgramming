// Make my own 'ls -l | more' program using pipe & dup system call
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int 
main() 
{
	int fd[2];
	pid_t child;

	// make a pipe
	if(pipe(fd) == -1)  {
		perror("pipe");
		exit(1);
		}
 	
	// make process
	child = fork();
	if(child == (pid_t)(-1))  {
        	perror("fork");
			exit(1);
		}
	// ls -l -> fd[1] -> fd[0] -> more

	// child process
	else if(child == (pid_t)0) {
        	close(1);	// close the STDOUT
			close(fd[0]); // close the fd[0] (read)
        	
			// duplicate,  STDOUT -> fd[1]
			// now 1==fd[1], same fd
			// same as dup2(fd[1],1)
        	if(dup(fd[1]) == -1)  {
        		perror("dup");
				exit(1);
			}
			// execute ls -l 
        	if((execlp("ls", "ls", "-l", NULL)) == -1)  {
        		perror("execlp");
				exit(1);
			}
	} 
	// parent process
	else {
        	close(0); //close the STDIN
			close(fd[1]); // close the fd[1] :write
        	
			// STDIN -> fd[0]
			// now 0 == fd[0], same fd 
			// same as dup(fd[0])
        	if(dup2(fd[0], 0) == -1)  {
        		perror("dup");
				exit(1);
			}
			
        	if((execlp("more", "more", NULL)) == -1)  {
        		perror("execlp");
			exit(1);
		}
	}
 
	return 0;
}
