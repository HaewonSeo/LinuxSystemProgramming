#include <stdio.h>

 
// length of string,  move the pointer of string and count len.
int strlen_p(char *str)
{
	int len=0;
	while(*str++){
		len++;
	}
	return len;
}

// count i before str[i] == '\0' (NULL termination)
int strlen_a(char str[])
{
	int i;
	for(i =0; str[i] != '\0'; i++);
		
	return i;
}

// string copy, *src -> *dst.  
void strcpy_p(char *dst, char *src)
{
	while(*src){
			*dst++ = *src++;
	}
	// last '\0' copy
	*dst = *src;
}

// string copy before src[i] == "\0"
void strcpy_a(char dst[], char src[])
{
	int i;
	for(i=0; src[i] != '\0' ; i++)
		dst[i] = src[i];
	// last '\0' copy
	dst[i] = src[i];
}

// string catenation, *dst+*src
void strcat_p(char *dst, char *src)
{
	// move to end of dst
	while(*dst++);
	// back one byte because of the NULL 
	dst--;
	// catenation src 
	while(*src)	{
		*dst++=*src++;
	}
	// last '\0' copy
	*dst = *src;
}

// string catenation, dst[] + src[]
void strcat_a(char dst[], char src[])
{
	int i,j;
	//count i
	for(i=0; dst[i] != '\0'; i++);
	for(j=0; src[j] != '\0'; j++)
			// string catenation through i&j  
			dst[i+j] = src[j];
	
}

// string compare by ASCII Code
int strcmp_p(char *dst, char *src)
{	
	while(1){
		// if *dst == *src , continue the while() 
		if(*dst == *src){
			*dst++;
			*src++;
			if( (*dst == '\0') && (*src == '\0') )
				return 0;
			else
				continue;
		}
		// if *dst > *src , return 1
		else if(*dst > *src) 
			return 1;
		// if *dst < *src , return -1
		else
			return -1;
	}
}

//string compare by ASCII code,  NULL is ASCII 0. 
int strcmp_a(char dst[], char src[])
{
	int i;
	for(i=0; ; i++)
	{
		// if dst[i] > src[i] return 1
		if(dst[i] > src[i])
			return 1;
		// if dst[i] < src[i] return -1	
		else if(dst[i] < src[i])
			return -1;
		// if dst[] == src[] return 0
		else if( (dst[i]=='\0') && (src[i]=='\0'))
			return 0;
		//just dst[i] == src[i] continue next i
		else 
			continue;
	}			

	
}


int main()

{
	int 		len1, len2;
	char	str1[20], str2[20];

	len1 = strlen_p("Hello");
	len2 = strlen_a("Hello");
	printf("strlen: p=%d, a=%d\n", len1, len2);

	strcpy_p(str1, "Hello");
	strcpy_a(str2, "Hello");
	printf("strcpy: p=%s, a=%s\n", str1, str2);

	strcat_p(str1, ",World!");
	strcat_a(str2, ",World!");
	printf("strcat: p=%s, a=%s\n", str1, str2);
	
	int			cmp1, cmp2;
	// Now str1,str2 is "Hello, World!"
	printf("\nstr1,str2 : \"Hello,World!\"\n");
	
	// Case1 : compare with "hello,world!"
	printf("[Case1] Compare with 'hello,world!'\n");
	cmp1 = strcmp_p(str1, "hello,world!");
	cmp2 = strcmp_a(str2, "hello,world!");
	printf("strcmp: p=%d, a=%d\n", cmp1, cmp2);
	
	// Case2 : compare with "AAAA"
	printf("[Case2] Compare with 'AAAA'\n");
	cmp1 = strcmp_p(str1, "AAAA");
	cmp2 = strcmp_a(str2, "AAAA");
	printf("strcmp: p=%d, a=%d\n", cmp1, cmp2);
	
	// Case3 : compare with "Hello,World!"
	printf("[Case3] Compare with 'Hello,World!'\n");
	cmp1 = strcmp_p(str1, "Hello,World!");
	cmp2 = strcmp_a(str2, "Hello,World!");
	printf("strcmp: p=%d, a=%d\n", cmp1, cmp2);
	
	return 0;
}


