// A program with race condition
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void
CharAtaTime(char *str)
{
	char	*ptr;
	int		c, i;

	setbuf(stdout, NULL);
	for (ptr = str ; c = *ptr++ ; )  {
		for(i = 0 ; i < 999999 ; i++)
			;
		// int putc(int character, FILE* stream);
		putc(c, stdout);
	}
}

void
main()
{
	pid_t	pid;

	// error check
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		CharAtaTime("output from child\n");
	} 
	else  {
		CharAtaTime("output from parent\n");
	}
}
