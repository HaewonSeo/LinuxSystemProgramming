// Convert a text file into a binary file
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h" 

void main(int argc, char *argv[])
{
	FILE	*src, *dst;
	Record	rec;

	// if the number of arguments, print the error message
	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source dest\n", argv[0]);
		exit(1);
	}
	
	// open the argv[1] for read textfile
	if ((src = fopen(argv[1], "rt")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	// open the arg[2] for write binary file
	if ((dst = fopen(argv[2], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	// get strings from the src file
	while (fgets(rec.stud, SMAX, src))  {
		// strchr() returns the pointer of '\n' in rec.stud
		// replace '\n' to '\0' for making null-terminated string
		*strchr(rec.stud, '\n') = '\0';
		fgets(rec.num, NMAX, src);
		*strchr(rec.num, '\n') = '\0';
		fgets(rec.dept, DMAX, src);
		*strchr(rec.dept, '\n') = '\0';

		fwrite(&rec, sizeof(rec), 1, dst);
	}

	// close the files 
	fclose(src);
	fclose(dst);
}
