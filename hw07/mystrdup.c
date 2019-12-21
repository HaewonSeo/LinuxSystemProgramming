#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *
mystrdup(char *s1)
{	
	//dynamic memory allocaton, NULL termination
	char *s2 = (char *)malloc(strlen(s1)+1);
	strcpy(s2,s1); // string copy
	return s2;
}

void
main()
{
	char str1[] = "Hello";
	char *str2;

	// duplicate the str1
	str2 = mystrdup(str1);
	puts(str2);
	
	// free for str2
	free(str2);
	
}
