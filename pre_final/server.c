#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "tcp.h"
#include <stdlib.h>
#include <fcntl.h>
int	Sockfd;

void
CloseServer()
{
	close(Sockfd);
	printf("\nTCP Server exit.....\n");

	exit(0);
}


main(int argc, char *argv[])
{
	int					newSockfd, cliAddrLen, n;
	struct sockaddr_in	cliAddr, servAddr;
	MsgType				msg;
	int					pid;
	int 				count;
	int					fd;

	signal(SIGINT, CloseServer);

	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	listen(Sockfd, 5);

	cliAddrLen = sizeof(cliAddr);
	while (1)  {

		if( (pid = fork()) <0) {
			perror("fork");
			exit(1);
		}
		
		else if( pid == 0 ) {
			newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
			if (newSockfd < 0)  {
				perror("accept");
				exit(1);
			}
		
			if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
				perror("read");
				exit(1);
			}

			if ((fd = open(msg.filename, O_APPEND | O_CREAT)) == NULL)  {
				perror("fopen");
				exit(1);
			}
			

		 	write(fd, msg.sec, 	sizeof(long));
			write(fd, msg.usec, sizeof(long));
	
			usleep(10000);
			close(newSockfd);
			exit(0);
			}

		else{
			wait(NULL);
		}

	}
}
