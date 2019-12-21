// Access the binary file
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> // for strcpy
#include "record.h"


// print the member datas of Record structure
void
print_record(Record *rp)
{
	puts(rp->stud);
	puts(rp->num);
	puts(rp->dept);
}

void main(int argc, char *argv[])
{
	FILE	*fp;
	Record	rec;
	
	// check the argc==2
	if (argc != 2)  {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}
	
	// open the argv[1] for read+write binary file.
	// write for data updating
	if ((fp = fopen(argv[1], "r+b")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	printf("-----Ordered Record List-----\n");
	
	// file read & print the record's member data
	while (fread(&rec, sizeof(rec), 1, fp))  {
		print_record(&rec);
	}
	// set file position to the beginning of the file 
	rewind(fp);
	// get character from stdin buffer
	getchar();

	printf("-----Shuffled Record List (3, 6, 2, 4, 1, 5)-----\n");
	// Print List 3
	// L means long 
	// move the position 2L*sizeof(rec) from ahead of file
	fseek(fp, sizeof(rec)*2L, SEEK_SET);
	// read rec from fp
	fread(&rec, sizeof(rec), 1, fp);
	// print rec
	print_record(&rec);

	// Print List 6
	fseek(fp, sizeof(rec)*5L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);
	
	// Print List 2 
	fseek(fp, sizeof(rec)*1L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);

	// Print List 4
	fseek(fp, sizeof(rec)*3L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);

	// Print List 1
	fseek(fp, sizeof(rec)*0L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);

	// Print List 5
	fseek(fp, sizeof(rec)*4L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);
	
	// get a char from stdin
	getchar();

	printf("-----Updated Record List-----\n");
	
	// Update the dept of List 3 
	fseek(fp, sizeof(rec)*2L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	strcpy(rec.dept, "Movie");
	// move the postion 
	fseek(fp, sizeof(rec)*2L, SEEK_SET);
	// rewrite the rec data
	fwrite(&rec, sizeof(rec), 1, fp);
	
	// Update the dept of List 6
	fseek(fp, sizeof(rec)*5L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	strcpy(rec.dept, "Baseball");
	// move the postion
	fseek(fp, sizeof(rec)*5L, SEEK_SET);
	// rewrite the rec data
	fwrite(&rec, sizeof(rec), 1, fp);
	
	// set the file position to the beginning of the file
	rewind(fp);
	
	// print the all record datas of fp
	while (fread(&rec, sizeof(rec), 1, fp))  {
		print_record(&rec);
	}
	
	// close the fp
	fclose(fp);
}
