// Synchronous I/O multiplexing example

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include "select.h"
#include <stdlib.h>

int	TcpSockfd;
int	UdpSockfd;
int	UcoSockfd;
int	UclSockfd;

void
CloseServer()
{
	// close the socket
	close(TcpSockfd);
	close(UdpSockfd);
	close(UcoSockfd);
	close(UclSockfd);
	// remove the TCP&UDP path
	if (remove(UNIX_STR_PATH) < 0)  {
		perror("remove");
	}
	if (remove(UNIX_DG_PATH) < 0)  {
		perror("remove");
	}

	printf("\nServer daemon exit.....\n");

	exit(0);
}

void
MakeTcpSocket()
{
	struct sockaddr_in	servAddr;
	
	// SOCKET
	if ((TcpSockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	// BIND
	if (bind(TcpSockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	// LISTEN
	listen(TcpSockfd, 5);
}

void
MakeUdpSocket()
{
	struct sockaddr_in	servAddr;
	
	// SOCKET
	if ((UdpSockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_UDP_PORT);

	// BIND
	if (bind(UdpSockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

}

void
MakeUcoSocket()
{
	struct sockaddr_un	servAddr;
	int					servAddrLen;

	// SOCKET
	if ((UcoSockfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sun_family = PF_UNIX;
	strcpy(servAddr.sun_path, UNIX_STR_PATH);
	servAddrLen = strlen(servAddr.sun_path) + sizeof(servAddr.sun_family);

	// BIND
	if (bind(UcoSockfd, (struct sockaddr *) &servAddr, servAddrLen) < 0)  {
		perror("bind");
		exit(1);
	}

	// LISTEN
	listen(UcoSockfd, 5);

}

void
MakeUclSocket()
{
	struct sockaddr_un	servAddr;
	int					servAddrLen;

	// SOCKET
	if ((UclSockfd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sun_family = PF_UNIX;
	strcpy(servAddr.sun_path, UNIX_DG_PATH);
	servAddrLen = strlen(servAddr.sun_path) + sizeof(servAddr.sun_family);

	// BIND
	if (bind(UclSockfd, (struct sockaddr *) &servAddr, servAddrLen) < 0)  {
		perror("bind");
		exit(1);
	}

}

void
ProcessTcpRequest()
{
	int					newSockfd, cliAddrLen, n;
	struct sockaddr_in	cliAddr;
	MsgType				msg;

	// ACCEPT
	cliAddrLen = sizeof(cliAddr);
	newSockfd = accept(TcpSockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
	if (newSockfd < 0)  {
		perror("accept");
		exit(1);
	}
		
	// READ
	if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
		perror("read");
		exit(1);
	}
	printf("Received TCP request: %s.....", msg.data);

	// WRITE
	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());
	if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
		perror("write");
		exit(1);
	}
	printf("Replied.\n");

	// CLOSE
	close(newSockfd);
}

void
ProcessUdpRequest()
{
	int					cliAddrLen, n;
	struct sockaddr_in	cliAddr;
	MsgType				msg;

	// REVFROM
	cliAddrLen = sizeof(cliAddr);
	if ((n = recvfrom(UdpSockfd, (char *)&msg, sizeof(msg), 
				0, (struct sockaddr *)&cliAddr, &cliAddrLen)) < 0)  {
		perror("recvfrom");
		exit(1);
	}
	printf("Received UDP request: %s.....", msg.data);

	// SENDTO
	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());
	if (sendto(UdpSockfd, (char *)&msg, sizeof(msg),
				0, (struct sockaddr *)&cliAddr, cliAddrLen) < 0)  {
		perror("sendto");
		exit(1);
	}
	printf("Replied.\n");
}

void
ProcessUcoRequest()
{
	int					newSockfd, cliAddrLen, n;
	struct sockaddr_un	cliAddr;
	MsgType				msg;

	// ACCEPT
	cliAddrLen = sizeof(cliAddr);
	newSockfd = accept(UcoSockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
	if (newSockfd < 0)  {
		perror("accept");
		exit(1);
	}
		
	// READ
	if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
		perror("read");
		exit(1);
	}
	printf("Received UNIX-domain CO request: %s.....", msg.data);

	// WRITE
	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());
	if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
		perror("write");
		exit(1);
	}
	printf("Replied.\n");

	// CLOSE
	close(newSockfd);
}

void
ProcessUclRequest()
{
	int					cliAddrLen, n;
	struct sockaddr_un	cliAddr;
	MsgType				msg;

	// REVFROM
	cliAddrLen = sizeof(cliAddr);
	if ((n = recvfrom(UclSockfd, (char *)&msg, sizeof(msg), 
				0, (struct sockaddr *)&cliAddr, &cliAddrLen)) < 0)  {
		perror("recvfrom");
		exit(1);
	}
	printf("Received UNIX-domain CL request: %s.....", msg.data);

	// SENDTO
	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());
	if (sendto(UclSockfd, (char *)&msg, sizeof(msg),
				0, (struct sockaddr *)&cliAddr, cliAddrLen) < 0)  {
		perror("sendto");
		exit(1);
	}
	printf("Replied.\n");
}

void
main(int argc, char *argv[])
{
	fd_set	fdvar;
	int		count;

	// register a signal handler
	signal(SIGINT, CloseServer);

	// make socket
	MakeTcpSocket();
	MakeUdpSocket();
	MakeUcoSocket();
	MakeUclSocket();

	printf("Server daemon started.....\n");

	while (1)  {
		// set socket to fdvar
		FD_ZERO(&fdvar);
		FD_SET(TcpSockfd, &fdvar);
		FD_SET(UdpSockfd, &fdvar);
		FD_SET(UcoSockfd, &fdvar);
		FD_SET(UclSockfd, &fdvar);

		// creted sd 3,4,5,6. Check only sd in fdvar among 0~9 sd.
		if ((count = select(10, &fdvar, (fd_set *)NULL, (fd_set *)NULL, 
			(struct timeval *)NULL)) < 0)  {
			perror("select");
			exit(1);
		}
		// identify the sd
		while (count--)  {
			if (FD_ISSET(TcpSockfd, &fdvar))  {
				ProcessTcpRequest();
			}
			else if (FD_ISSET(UdpSockfd, &fdvar))  {
				ProcessUdpRequest();
			}
			else if (FD_ISSET(UcoSockfd, &fdvar))  {
				ProcessUcoRequest();
			}
			else if (FD_ISSET(UclSockfd, &fdvar))  {
				ProcessUclRequest();
			}
		}
	}
}
