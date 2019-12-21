#include <stdio.h>

void main()
{
	char c = 'a', s[] = "hello";
	int i = 100; long l = 99999;
	float f = 3.14; double d = 99.999;
	int *p = &i;
	
	//char, string, decimal, Hexa(ex.0xABCD), float, double, pointer
	printf("Output: %c %s %d %#X %ld %.4f %.2lf %p\n", c, s, i, i, l, f, d, p); 
	//char
	putchar(c);
	//string
	puts(s);
}

