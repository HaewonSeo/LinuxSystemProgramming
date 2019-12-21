//List a text file with line numbers
#include <stdio.h>
#include <stdlib.h>

#define	MAX_BUF	256

void main(int argc, char *argv[])
{
	FILE	*fp;
	char	buf[MAX_BUF];
	int		line;
	
	// check the argc is 2 
	if (argc != 2)  {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

	// open the file for read_text file
	if ((fp = fopen(argv[1], "rt")) == NULL)  {
		perror("fopen"); //print error message
		exit(1);
	}

	line = 1;
	// file get string, to buffer
	while (fgets(buf, MAX_BUF, fp))  {
		printf("%4d: %s", line++, buf); // %4d : always output in 4 digits.
	}

	fclose(fp);
}
