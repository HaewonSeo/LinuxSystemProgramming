// Copy text file by character
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
    FILE	*src, *dst;
    int		ch;
    
    // it needs 3 arguments
    if (argc != 3)  {
        fprintf(stderr, "Usage: %s source destination\n", argv[0]);
        exit(1);
    }

    // fopen returns NULL on error
    // file open for read_text
    if ((src = fopen(argv[1], "rt")) == NULL)  {
        perror("fopen");
        exit(1);
    }
    
    // file open for write_text
    if ((dst = fopen(argv[2], "wt")) == NULL)  {
        perror("fopen");
        exit(1);
    }
    
    // if ch == EOF, breaks the loop
    while ( (ch = fgetc(src)) != EOF  )  {
        fputc(ch, dst); //write acharacter in argv[2] file
    } 

    //close the files
    fclose(src);
    fclose(dst);
}
