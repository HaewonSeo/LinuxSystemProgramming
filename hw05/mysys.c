#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int
mysystem(char *cmd)
{
	pid_t	pid;
	char	tmp[10], *tmp2;
	char *str[10]={NULL,};
	int i;
	
	// divide the *cmd string using strtok()
	i=0;
	strcpy(tmp,cmd);
	tmp2 = strtok(tmp," ");
	str[i++] = tmp2; //str[0] : "ls"

	while(tmp2){
		//printf("\n%s",tmp2);  //for checking
		tmp2 = strtok(NULL," ");
		str[i++] = tmp2;
	}

	// create process
	if( (pid = fork()) < 0 ) {
		perror("fork");
		exit(1);
	}

	// child process, execv()
	else if( pid == 0){
		if( execvp(str[0], str) < 0 ){
			perror("execvp");
			exit(1);
		}
	}

	// wait for child process termination
	else{
		if( waitpid(pid, NULL, 0) <0 ){
			perror("waitpid");
			exit(1);
		}
	}

	return 1;
}

void
main()
{
	int status;
	char buf[10];
	// get a command through stdin	
	printf("CMD> ");
	gets(buf,10,stdin);

	if( (status = mysystem(buf)) < 0){
		perror("mysystem");
		exit(1);
	}
}
