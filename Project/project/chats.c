// Project1 : Process multiplexing using select system call instead of multi-threads
// Chatting Server
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "chat.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define	DEBUG

#define	MAX_CLIENT	5
#define	MAX_ID		32
#define	MAX_BUF		256

typedef	struct  {
	int			sockfd;
	int			inUse;
	pthread_t	tid;
	char		uid[MAX_ID];
	int			notFirst;
}
	ClientType;

int				Sockfd;

ClientType		Client[MAX_CLIENT];


// get unused id
int
GetID()
{
	int	i;

	for (i = 0 ; i < MAX_CLIENT ; i++)  {
		if (! Client[i].inUse)  {
			Client[i].inUse = 1;
			return i;
		}
	}
}

void
SendToOtherClients(int id, char *buf)
{
	int		i;
	char	msg[MAX_BUF+MAX_ID];

	sprintf(msg, "%s> %s", Client[id].uid, buf);

#ifdef	DEBUG
	printf("%s", msg);
	fflush(stdout);
#endif

	for (i = 0 ; i < MAX_CLIENT ; i++)  {
		if (Client[i].inUse && (i != id))  {
			//SEND message to other clients's sockfd
			if (send(Client[i].sockfd, msg, strlen(msg)+1, 0) < 0)  {
				perror("send");
				exit(1);
			}
		}
	}
}
	

void
ProcessClient(int id)
{
	char	buf[MAX_BUF];
	int		n;

	// First, receive the log-in information 
	if(!Client[id].notFirst){
		//RECV a client id and uid
		if ((n = recv(Client[id].sockfd, Client[id].uid, MAX_ID, 0)) < 0)  {
			perror("recv");
			exit(1);
		}
		printf("Client %d log-in(ID: %s).....\n", id, Client[id].uid);
		Client[id].notFirst = 1;	 //set Client.notFirst to true
	}
	// General case
	else  {
		//RECV the message
		if ((n = recv(Client[id].sockfd, buf, MAX_BUF, 0)) < 0)  {
			perror("recv");
			exit(1);
		}
		SendToOtherClients(id,buf);
	}

	//	if recv return 0, that means client[id].sockfd is closed.
	if (n == 0)  {
		printf("Client %d log-out(ID: %s).....\n", id, Client[id].uid);

		close(Client[id].sockfd);			//close the sockfd
		Client[id].inUse = 0;				//initialize the Client[id].inUse
		Client[id].notFirst = 0;			//initialize the Client[id].notFirst
		strcpy(buf, "log-out.....\n");

		SendToOtherClients(id, buf);
	}
}



void
CloseServer(int signo)
{
	int		i;

	//close the sockfd
	close(Sockfd);

	for (i = 0 ; i < MAX_CLIENT ; i++)  {
		if (Client[i].inUse)  {
			//close the client.sockfd
			close(Client[i].sockfd);
		}
	}
	printf("\nChat server terminated.....\n");

	exit(0);
}

void
main(int argc, char *argv[])
{
	int					newSockfd, cliAddrLen, id, one = 1, count, i;
	struct sockaddr_in	cliAddr, servAddr;
	fd_set				fdset;
	int					pid;

	//Register a signal handler
	signal(SIGINT, CloseServer);

	//SOCKET
	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	if (setsockopt(Sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0)  {
		perror("setsockopt");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	//BIND
	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	//LISTEN
	listen(Sockfd, 5);

	printf("Chat server started.....\n");

	cliAddrLen = sizeof(cliAddr);

	while (1)  {
		
		FD_ZERO(&fdset);
		FD_SET(Sockfd, &fdset);

		for(i=0; i<MAX_CLIENT; i++){ 
			if(Client[i].inUse)
				FD_SET(Client[i].sockfd, &fdset);
		}

		if ((count = select(10, &fdset, (fd_set *)NULL, (fd_set *)NULL,
			(struct timeval *)NULL)) < 0)  {
			perror("select");
			exit(1);
		}

		while(count--) {

			if(FD_ISSET(Sockfd, &fdset)){
				//ACCEPT
				newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
				if (newSockfd < 0)  {
					perror("accept");
					exit(1);
				}

				id = GetID();
				Client[id].sockfd = newSockfd;
			}

			else{
				for(i=0; i<MAX_CLIENT; i++){
					if( (Client[i].inUse) && FD_ISSET(Client[i].sockfd, &fdset))  {
						ProcessClient(i);
					}
				}
			}
		}
	
	
	
	}
}
