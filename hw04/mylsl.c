// This program works like '$ls -l'
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define MAX_COUNT 80 
#define MAX_FILENAME 20
#define MAX_BUF 40

struct LsInfo{
		char	permission[11];
		int		numlink;
		char	*userid;
		char	*groupid;
		int		size;
		char	time[MAX_BUF];
		char	filename[MAX_FILENAME];
};

// get mode and permission of file
void GetFileMode(struct stat *buf, struct LsInfo *info)
{		
	// set to the dafault value
	strcpy(info->permission, "----------");

	// get file mode
	if (S_ISREG(buf->st_mode))
		info->permission[0]='-';
	else if (S_ISDIR(buf->st_mode))
		info->permission[0]='d';
	else if (S_ISCHR(buf->st_mode))
		info->permission[0]='c';
	else if (S_ISBLK(buf->st_mode))
		info->permission[0]='b';
	else if (S_ISFIFO(buf->st_mode))
		info->permission[0]='P';
	else if (S_ISLNK(buf->st_mode))
		info->permission[0]='l';
	else if (S_ISSOCK(buf->st_mode))
		info->permission[0]='s';

	// get user permission
	if(buf->st_mode & S_IRUSR)
		info->permission[1]='r';
	if(buf->st_mode & S_IWUSR)
		info->permission[2]='w';
	if(buf->st_mode & S_IXUSR)
		info->permission[3]='x';
	else if(buf->st_mode & S_ISUID)
		info->permission[3]='S';

	// get group permission
	if(buf->st_mode & S_IRGRP)
		info->permission[4]='r';
	if(buf->st_mode & S_IWGRP)
		info->permission[5]='w';
	if(buf->st_mode & S_IXGRP)
		info->permission[6]='x';
	else if(buf->st_mode & S_ISGID)
		info->permission[6]='S';

	// get other permission
	if(buf->st_mode & S_IROTH)
		info->permission[7]='r';
	if(buf->st_mode & S_IWOTH)
		info->permission[8]='w';
	if(buf->st_mode & S_IXOTH){	
		// set stiky bit (for tmp file&directory)
		if(buf->st_mode & S_ISVTX)
			info->permission[9]='t';
		else
			info->permission[9]='x';
	}
	else if(buf->st_mode & S_ISVTX)
		info->permission[9]='T';
}

// get number of links
void GetNumLink(struct stat *buf, struct LsInfo *info)
{	
	info->numlink = buf->st_nlink;
}

// get user id and group id
void GetId(struct stat *buf, struct LsInfo *info)
{	
	// get user id
	struct passwd *pwd;
	uid_t usrid = buf->st_uid;
	pwd = getpwuid(usrid);
	info->userid = pwd->pw_name;
	
	// get group id
	struct group *g;
	gid_t grpid = buf->st_gid;
	g = getgrgid(grpid);
	info->groupid = g->gr_name;
}

// get file size
void GetSize(struct stat *buf, struct LsInfo *info)
{	
	info->size = buf->st_size;
}

// get date and time of last modification
void GetDateTime(struct stat *buf, struct LsInfo *info)
{
	time_t		tm;
	struct tm	*lctm;
	char		timebuf[MAX_BUF];

	tm = buf->st_mtime;
	lctm = localtime(&tm);
	strftime(timebuf, MAX_BUF, "%b %d %H:%M", lctm);
	strcpy(info->time,timebuf);
}

// print information of file
void PrintInfo(struct LsInfo *info)
{	
	printf("%s ",info->permission);
	printf("%d ",info->numlink);
	printf("%s ",info->userid);
	printf("%s ",info->groupid);
	printf("%5d ",info->size);
	printf("%s ",info->time);
	printf("%s\n",info->filename);
}

void main()
{
	DIR				*dp;
	struct dirent	*dep;
	struct stat		statbuf;
	struct LsInfo	lsinfo;
	char			filename[MAX_COUNT][MAX_FILENAME];
	int				count;
	int				i;
	int				j;
	char			tmp[MAX_FILENAME];
	char			fullpath[MAX_FILENAME];
	
	// open current directory 
	if( (dp = opendir(".")) == NULL) {
		perror("opendir");
		exit(1);
	}

	// get array of filenames in current directory
	count = 0;
	while( (dep = readdir(dp)) && count<MAX_COUNT) {
		if(strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)
			continue;
		strcpy( filename[count] , dep->d_name);
		count++;
	}

	// close directory pointer
	closedir(dp);
	
	// bubble sorting by filename for ascending order
	for(i=0; i<count; i++){
		for(j=0; j<count-(i+1); j++){
			if( strcasecmp(filename[j] , filename[j+1]) > 0 ){
				strcpy(tmp , filename[j+1]);
				strcpy(filename[j+1] , filename[j]);
				strcpy(filename[j] , tmp);
			}
		}
	}

	for(i=0; i<count; i++){	
		// get 'stat' structure of the file
		strcpy(fullpath, "./");
		strcat(fullpath, filename[i]);
		if(lstat(fullpath, &statbuf) < 0) {
			perror("lstat");
			exit(1);
		}
		
		// save information of the file to 'LsInfo' structure
		GetFileMode(&statbuf, &lsinfo);
		GetNumLink(&statbuf, &lsinfo);
		GetId(&statbuf, &lsinfo);
		GetSize(&statbuf, &lsinfo);
		GetDateTime(&statbuf, &lsinfo);
		strcpy(lsinfo.filename , filename[i]);
		
		// print information of the file
		PrintInfo(&lsinfo);
	}
}
