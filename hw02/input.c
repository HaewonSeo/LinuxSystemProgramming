#include <stdio.h>

void main()
{
	char c, s[80];
	int i; long l;
	float f; double d;
	
	//char, string, decimal, long-decimal, floating-number, double
	scanf("%c %s %d %ld %f %lf", &c, s, &i, &l, &f, &d); 
	printf("Output: %c %s %d %ld %.4f %.2lf\n", c, s, i, l, f, d); 

	// one character get&put
	c = getchar();
	putchar(c);
	
	// string get&put
	gets(s);
	puts(s);
}

