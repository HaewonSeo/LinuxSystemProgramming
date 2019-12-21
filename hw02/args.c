#include <stdio.h>

void main(int argc, char *argv[])
{
	int		i;
	// print argc, argv[]
	for (i = 0 ; i < argc ; i++)
		printf("argv[%d]=%s\n", i, argv[i]);
}

