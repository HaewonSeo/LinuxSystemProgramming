//FIFO server
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "fifo.h"


void
SigIntHandler(int signo)
{
	// remove the server fifo(./.fifo) and then exit
	if (remove(SERV_FIFO) < 0)  {
		perror("remove");
		exit(1);
	}
	
	exit(0);
}

void
main()
{
	int			fd, cfd, n;
	MsgType		msg;
	
	//register signal handler
	if (signal(SIGINT, SigIntHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}
 	
	// make fifo, set a permission : read&write for just owner
	// named as .fifo -> for hidden file 
	if (mkfifo(SERV_FIFO, 0600) < 0)  {
		if (errno != EEXIST)  { // file already exist 
			perror("mkfifo");
			exit(1);
		}
	}
	// Actually read only
	if ((fd = open(SERV_FIFO, O_RDWR)) < 0)  {
		perror("open");
		exit(1);
	}

	while (1)  {
		//wait for data is coming
		if ((n = read(fd, (char *)&msg, sizeof(msg))) < 0)  {
			// just any signal is comed, then continue the while(1) loop
			if (errno == EINTR)  { //interrupted system call
				continue;
			}
			else  {
				perror("read");
				exit(1);
			}
		}
		printf("Received request: %s.....", msg.data);

		if ((cfd = open(msg.returnFifo, O_WRONLY)) < 0)  {
			perror("open");
			exit(1);
		}
		sprintf(msg.data, "This is a reply from %d.", getpid());
		write(cfd, (char *)&msg, sizeof(msg));
		close(cfd);
		printf("Replied.\n");
	}
}
