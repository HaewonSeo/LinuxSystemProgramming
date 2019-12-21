// Reading a directory
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
void main()
{	
	// directory pointer
	DIR				*dp;
	// struct dirent has i-node number and Null-terminated file name
	struct dirent	*dep; 
	// DIR *opendir(char *pathname);
	// opendir() returns NULL on error
	if ((dp = opendir(".")) == NULL)  {
		perror("opendir");
		exit(1);
	}
	// struct dirent *readdir(DIR *dp);
	// print all file name 
	while (dep = readdir(dp))  {
		printf("%s\n", dep->d_name);
	}
	
	// close the directory
	closedir(dp);
}
