//Domain name service

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "tcp.h"

void
main(int argc, char *argv[])
{
	int					sockfd, n;
	struct sockaddr_in	servAddr;
	MsgType				msg;
	struct hostent		*hp;
	
	// check the argc
	if (argc != 2)  {
		fprintf(stderr, "Usage: %s IPaddress\n", argv[0]);
		exit(1);
	}

	// SOCKET
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	// initialize a servAddr
	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_port = htons(SERV_TCP_PORT);

	// (ex1) argv[1] : 127.0.0.1
	if (isdigit(argv[1][0]))  {
		// inet_addr : return 32-bit address for dotted decimal notation 
		servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	}
	else  {
		// if argv[1] is NULL, exit
		// gethostbyname : return pointer to hostent structure of argv[1] 
		if ((hp = gethostbyname(argv[1])) == NULL)  {
			fprintf(stderr, "Unknown host: %s\n", argv[1]);
			exit(1);
		}
		// memcpy(void* destination, void* source, size_t num)
		// 4 bytes 
		memcpy(&servAddr.sin_addr, hp->h_addr, hp->h_length);
	}

	// CONNECT
	if (connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("connect");
		exit(1);
	}

	// WRITE
	msg.type = MSG_REQUEST;
	sprintf(msg.data, "This is a request from %d.", getpid());
	if (write(sockfd, (char *)&msg, sizeof(msg)) < 0)  {
		perror("write");
		exit(1);
	}
	printf("Sent a request.....");
		
	// READ
	if ((n = read(sockfd, (char *)&msg, sizeof(msg))) < 0)  {
		perror("read");
		exit(1);
	}
	printf("Received reply: %s\n", msg.data);

	// CLOSE
	close(sockfd);
}
