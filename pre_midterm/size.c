#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATH 256

void
main(int argc, char *argv[]){

	struct stat		statbuf;
	DIR				*dp;
	struct dirent	*dep;
	char			fullpath[256];
	if (argc != 2)  {
		fprintf(stderr, "Usage: %s size\n", argv[0]);
		exit(1);
	}
	
	if ((dp = opendir(".")) == NULL)  {
		perror("opendir");
		exit(1);
	}

	while (dep = readdir(dp))  {
		if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)
				continue;
		strcpy(fullpath, ".");
		strcat(fullpath, "/");
		strcat(fullpath, dep->d_name);		
		
		if(lstat(fullpath, &statbuf)<0){
			perror("lstat");
			exit(1);
		}
		if( (statbuf.st_size) > atoi(argv[1])){

			printf("%s size : %d\n", dep->d_name, statbuf.st_size);
		}

	}
	
	closedir(dp);

}
