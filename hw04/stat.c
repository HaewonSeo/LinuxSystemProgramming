// Get file status
#include <stdio.h> // /usr/unclude/stdio.h
#include <sys/types.h> // /usr/include/x86_64-linux-gnu/sys/types.h
#include <sys/stat.h> // /usr/include/x86_64-linux-gnu/sys/stat.h , this file include <bits/stat.h>

void main(int argc, char *argv[])
{	
	// stat structure 
	struct stat	statbuf;
	char		*mode;
	int			i;
	
	for (i = 1 ; i < argc ; i++)  {
		printf("%s: ", argv[i]);
		// lstat gets symbolic link file's datas
		if (lstat(argv[i], &statbuf) < 0)  {
			perror("lstat");
			continue;
		}
		// check file type 
		if (S_ISREG(statbuf.st_mode))
			mode = "regular";
		else if (S_ISDIR(statbuf.st_mode))
			mode = "directory";
		else if (S_ISCHR(statbuf.st_mode))
			mode = "character special";
		else if (S_ISBLK(statbuf.st_mode))
			mode = "block special";
		else if (S_ISFIFO(statbuf.st_mode))
			mode = "FIFO";
		else if (S_ISLNK(statbuf.st_mode))
			mode = "symbolic link";
		else if (S_ISSOCK(statbuf.st_mode))
			mode = "socket";
		// print file stats
		printf("%s\n", mode);
		printf("\tst_mode = %d\n", statbuf.st_mode);
		printf("\tst_ino = %d\n", statbuf.st_ino);
		printf("\tst_dev = %d\n", statbuf.st_dev);
		printf("\tst_rdev = %d\n", statbuf.st_rdev);
		printf("\tst_nlink = %d\n", statbuf.st_nlink);
		printf("\tst_uid = %d\n", statbuf.st_uid);
		printf("\tst_gid = %d\n", statbuf.st_gid);
		printf("\tst_size = %d\n", statbuf.st_size);
		printf("\tst_atime = %d\n", statbuf.st_atime);
		printf("\tst_mtime = %d\n", statbuf.st_mtime);
		printf("\tst_ctime = %d\n", statbuf.st_ctime);
		printf("\tst_blksize = %d\n", statbuf.st_blksize);
		printf("\tst_blocks = %d\n", statbuf.st_blocks);
	}
}
