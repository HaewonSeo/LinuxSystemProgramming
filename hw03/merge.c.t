#include <stdio.h>
#include <stdlib.h>
#define	MAX_BUF	1024

void main(int argc, char *argv[])
{
    FILE	*src1, *src2, *dst;
    char	buf[MAX_BUF];
    int		count;

    // print a error message
    if (argc != 4)  {
        fprintf(stderr, "Usage: %s source1 source2 dest\n", argv[0]);
        exit(1);
    }

    // open the argv[1] for read binary file
    if ((src1 = fopen(argv[1], "rb")) == NULL)  {
        perror("fopen");
        exit(1);
    }
    // open the argv[2] for read binary file
    if ((src2 = fopen(argv[2], "rb")) == NULL)  {
        perror("fopen");
        exit(1);
    }
    // open the argv[3] for write binary file
    if ((dst = fopen(argv[3], "wb")) == NULL)  {
        perror("fopen");
        exit(1);
    }

    // copy the src1 file to the dst file
    // count the number of objects read 
    while ((count = fread(buf, 1, MAX_BUF, src1)) > 0)  {
        fwrite(buf, 1, count, dst);
    }

    // append the src2 file to the dst file, for merge src1 and src2 file 
    while ((count = fread(buf, 1, MAX_BUF, src2)) > 0)  {
        fwrite(buf, 1, count, dst);
    }

    // close the files
    fclose(src1);
    fclose(src2);
    fclose(dst);
}
