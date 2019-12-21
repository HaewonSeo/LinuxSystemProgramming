#include <stdio.h>


void del(char str[])
{
	int i;
	char dst[20];
	
	for(i=0; i<sizeof(str) ;i++){
		str[i] = str[i+1];
	}
}


main()
{
	char str[20] = "Hello";
	del(str);
	puts(str);
} 
