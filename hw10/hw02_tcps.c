// TCP sockek example
// TCP server
// hw02 : creat processes
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "tcp.h"
#include <stdlib.h>
#include <unistd.h>

int	Sockfd;

void
CloseServer()
{
	close(Sockfd);
	printf("\nTCP Server exit.....\n");

	exit(0);
}

void
main(int argc, char *argv[])
{
	int					newSockfd, cliAddrLen, n, i;
	struct sockaddr_in	cliAddr, servAddr; // PF_INET, IPv4
	MsgType				msg;
	int 				pid;

	// register a signal handler
	signal(SIGINT, CloseServer);

	// SOCKET
	// create a socket for TCP
	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	// initailize a servAddr 
	bzero( (char *)&servAddr, sizeof(servAddr) );
	servAddr.sin_family = PF_INET; //protocol family
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // network byte ordered 32-bit address
													// receive any IP addresses
	servAddr.sin_port = htons(SERV_TCP_PORT); // 7000 + ID, host to network(short) 
	
	// BIND
	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	// LISTEN
	listen(Sockfd, 5);

	printf("TCP Server started.....\n");

	// kernel allocate a cliAddr ifself
	cliAddrLen = sizeof(cliAddr);

	while(1)  {
		// make process
		if( (pid = fork()) <0 ){
			perror("fork");
			exit(1);
		}

		//child process
		else if( pid == 0 ){
			// ACCEPT
			newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
			if (newSockfd < 0)  {
				perror("accept");
				exit(1);
			}
			// READ
			if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
				perror("read");
				exit(1);
			}
			printf("Received request: %s.....", msg.data);
			
			// WRITE
			msg.type = MSG_REPLY;
			sprintf(msg.data, "This is a reply from %d.", getpid());
			if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
				perror("write");
				exit(1);
			}
			printf("Replied.\n");
			
			usleep(10000);
			// CLOSE
			close(newSockfd);
			exit(0);
		}

		//parent process
		else{
			wait(NULL);
		}
	}
	
}
