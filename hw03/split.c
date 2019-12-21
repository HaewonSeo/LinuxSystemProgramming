// Split a file into two
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define	MAX_BUF	1024

// get filesize
long
filesize(FILE *fp)
{
	long	cur, size;
	// get the current position
	cur = ftell(fp);
	// offset is 0L, 0L is a long integer value with all the bits set to zero
	// move the position to end of file
	fseek(fp, 0L, SEEK_END); 
	// now position is the file size
	size = ftell(fp);
	// return the poistion to current file position
	fseek(fp, cur, SEEK_SET);
	return(size);
}

void main(int argc, char *argv[])
{
	FILE	*src, *dst1, *dst2;
	char	buf[MAX_BUF];
	int		count, size;
	
	// if the number of argument is not 4, print a error message
	if (argc != 4)  {
		fprintf(stderr, "Usage: %s source dest1 dest2\n", argv[0]);
		exit(1);
	}
	
	// open a file for read binary file
	if ((src = fopen(argv[1], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	
	// open a file for write binary file
	if ((dst1 = fopen(argv[2], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	// open a file for write binary file
	if ((dst2 = fopen(argv[3], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	// get a half of file size
	size = filesize(src) / 2;

	// copy the front half of src file to the dst1 file
	while (size > 0)  {
		count = (size > MAX_BUF) ?  MAX_BUF : size;
		fread(buf, 1, count, src); 
		fwrite(buf, 1, count, dst1);
		size -= count; // size update
	}
	
	// copy the back half of src file to the dst2 file
	while ((count = fread(buf, 1, MAX_BUF, src)) > 0)  {
		fwrite(buf, 1, count, dst2);
	}
	
	//close the files
	fclose(src);
	fclose(dst1);
	fclose(dst2);
}
