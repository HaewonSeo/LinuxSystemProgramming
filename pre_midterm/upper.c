#include <stdio.h>
#include <string.h>
#include <ctype.h>

void
strupper(char str[])
{
	while(*str!='\0'){
		

	printf("1%s\n",str);
		*str = toupper(*str);
		 str++;
	}	

	printf("1%s\n",str);
}

void
main(){
	
	char str[]="hello, World";

	strupper(str);
	printf("%s\n",str);
}
