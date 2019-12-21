//Copy text file by strings
#include <stdio.h>
#include <stdlib.h>

#define	MAX_BUF	256

void main(int argc, char *argv[])
{
    FILE	*src, *dst;
    char	buf[MAX_BUF];
    
    // it needs 3 argc
    if (argc != 3)  {
        fprintf(stderr, "Usage: %s source destination\n", argv[0]);
        exit(1);
    }
    
    // open the file for read_text
    if ((src = fopen(argv[1], "rt")) == NULL)  {
        perror("fopen");
        exit(1);
    }
    
    // open the file for write_text
    if ((dst = fopen(argv[2], "wt")) == NULL)  {
        perror("fopen");
        exit(1);
    }
    
    // fgets returns the pointer of buffer if OK, NULL on EOF
    while ( (fgets(buf, MAX_BUF, src) != NULL ) ) {
        fputs(buf, dst);
    }
    
    // close the files
    fclose(src);
    fclose(dst);
}
