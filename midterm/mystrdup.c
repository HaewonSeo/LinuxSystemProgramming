#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strdup(const char *s){
	char *tmp =(char*)malloc(100*sizeof(char));
	strcpy(tmp,s);
	return tmp;
}

void
main()
{

	char str1[] = "Hello, Linux!";
	char *str2 = strdup(str1);
	puts(str2);


	free(str2);
}
