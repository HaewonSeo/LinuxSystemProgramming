// TCP socket example
// TCP Client
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp.h"

void
main(int argc, char *argv[])
{
	int					sockfd, n;
	struct sockaddr_in	servAddr;
	MsgType				msg;

	// SOCKET
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	// initialize the servAddr
	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET; // protocol family : PF_INET
	servAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR); //127.0.0.1.
														//convert dotted decimal notation to address
	servAddr.sin_port = htons(SERV_TCP_PORT); //7000 + ID

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
