// Make my own ls -R progame
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define	MAX_PATH	256

void
JustDoIt(char *path)
{
	DIR				*dp;
	struct dirent	*dep;
	struct stat		statbuf;
	char			fullpath[MAX_PATH];
	
	// open directory 
	if ((dp = opendir(path)) == NULL)  {
		perror("opendir");
		exit(1);
	}

	/*
	  .:
	  print file names in current directory 
	*/
	printf("\n%s:\n", path);
	while (dep = readdir(dp))  {
		// if d_name is '.' or '..', continue the loop.
		if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)
			continue;
		//print file name
		printf("%s\n", dep->d_name);
	}
	
	// rewind directory pointer
	rewinddir(dp);
	// find a directory
	while (dep = readdir(dp))  {
		if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)
			continue;
		// fullpath : "path" + "/" + "d_name"
		strcpy(fullpath, path);
		strcat(fullpath, "/");
		strcat(fullpath, dep->d_name);
		// get "fullpath" file status
		if (lstat(fullpath, &statbuf) < 0)  {
			perror("lstat");
			exit(1);
		}
		// if "fullpath" file is directory, execute JustDoIt() recursively
		if (S_ISDIR(statbuf.st_mode))  {
			JustDoIt(fullpath);
		}
	}
	
	// close the directory pointer
	closedir(dp);
}

void main()
{
	JustDoIt(".");
}
