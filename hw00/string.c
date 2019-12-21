#include <stdio.h>

int
strlen_p(char *str)
{
	int	len = 0;

	while (*str++)  {
		len++;
	}
	return len;
}

int
strlen_a(char str[])
{
	int i;

	for (i = 0 ; str[i] != '\0' ; i++)
		;
	return i;
}

void
strcpy_p(char *dst, char *src)
{
	while (*src)  {
		*dst++ = *src++;
	}
	*dst = *src;
}

void
strcpy_a(char dst[], char src[])
{
	int i;

	for (i = 0 ; src[i] != '\0' ; i++)
		dst[i] = src[i];
	dst[i] = src[i];
}

void
strcat_p(char *dst, char *src)
{
	while (*dst++)
		;
	dst--;
	while (*src)  {
		*dst++ = *src++;
	}
	*dst = *src;
}

void
strcat_a(char dst[], char src[])
{
	int i, j;

	for (i = 0 ; dst[i] != '\0' ; i++)
		;
	for (j = 0 ; src[j] != '\0' ; j++)
		dst[i+j] = src[j];
	dst[i+j] = src[j];
}

main()
{
	int		len1, len2;
	char	str1[20], str2[20];

	len1 = strlen_p("Hello");
	len2 = strlen_a("Hello");
	printf("strlen: p=%d, a=%d\n", len1, len2);

	strcpy_p(str1, "Hello");
	strcpy_a(str2, "Hello");
	printf("strcpy: p=%s, a=%s\n", str1, str2);

	strcat_p(str1, ", World!");
	strcat_a(str2, ", World!");
	printf("strcat: p=%s, a=%s\n", str1, str2);
}
