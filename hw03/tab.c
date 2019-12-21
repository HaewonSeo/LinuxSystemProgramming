// This program makes src file's tab size 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strcpy()

// #define FALSE 0
// #define TRUE 1
enum { FALSE, TRUE };

void
conv(char *fname)
{
	FILE	*src, *dst;
	char	fdest[40];
	int		ch, first;
	
	// open the file for read text file
	if ((src = fopen(fname, "rt")) == NULL)  {
		perror("fopen");
		return;
	}
	
	// copy fname to fdest
	strcpy(fdest, fname);
	// catenation, Thus fdest ==  fdest+".t"
	strcat(fdest, ".t");

	// open the file for write text file
	if ((dst = fopen(fdest, "wt")) == NULL)  {
		perror("fopen");
		return;
	}
	
	// declare first for operating only first '/t'
	first = TRUE;
	while ((ch = fgetc(src)) != EOF)  {
		// if meet '\t', put ' ' 4 times in dst file 
		if (first && ch == '\t')  {
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
		}
		else  {
			// copy the other characters
			fputc(ch, dst);
			// for checking only '\t' of bigining of line
			if (first)
				first = FALSE;
			// if position is the end of line, first becomes true
			if (ch == '\n')
				first = TRUE;
		}
	}
	
	// close th files
	fclose(src);
	fclose(dst);
}

void main(int argc, char *argv[])
{
	// operate all argv[n], but n>0
	while (--argc)  {
		conv(argv[argc]);
	}
}
