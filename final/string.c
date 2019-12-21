#include <stdio.h>
#include <string.h>
 

// string compare by ASCII Code
int strncmp_p(char *dst, char *src, int n)
{	
	int i;
	for(i=0; i<n; i++){
		// if *dst == *src , continue the while() 
		if(*dst == *src){
			*dst++;
			*src++;
			if( (*dst == '\0') && (*src == '\0') )
				return 0;
		}
		// if *dst > *src , return 1
		else if(*dst > *src){
			return 1;
			}
		// if *dst < *src , return -1
		else{
			return -1;
		}
	}
	return 0;
}

//string compare by ASCII code,  NULL is ASCII 0. 
int strncmp_a(char dst[], char src[], int n )
{
	int i;
	for(i=0; i<n; i++)
	{
		if(dst[i] == src[i])
			continue;
		// if dst[i] > src[i] return 1
		if(dst[i] > src[i])
			return 1;
		// if dst[i] < src[i] return -1	
		else if(dst[i] < src[i])
			return -1;
		// if dst[] == src[] return 0
		else if( (dst[i]=='\0') && (src[i]=='\0'))
			return 0;
	}			

	return 0;
	
}


int main()

{
	char		str[5];
	int			n;	
	int			cmp1, cmp2;

	strcpy(str,"abc");

	printf("str1 : \"abc\"\n");
	
	printf("[Case1] Compare with 'abc', compare 3 character\n");
	cmp1 = strncmp_p(str, "abc", 3);
	cmp2 = strncmp_a(str, "abc", 3);
	printf("strncmp: p=%d, a=%d\n", cmp1, cmp2);
	
	printf("[Case2] Compare with 'acb', compare 2 character\n");
	cmp1 = strncmp_p(str, "acb", 2);
	cmp2 = strncmp_a(str, "acb", 2);
	printf("strncmp: p=%d, a=%d\n", cmp1, cmp2);
	
	printf("[Case3] Compare with 'abx', compare 2 character\n");
	cmp1 = strncmp_p(str, "abx", 2);
	cmp2 = strncmp_a(str, "abx", 2);
	printf("strncmp: p=%d, a=%d\n", cmp1, cmp2);
	
	return 0;
}


