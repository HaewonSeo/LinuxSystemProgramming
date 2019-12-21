// Project2 : Process multiplexing using multi-thread instead of select system call
// Chatting Client
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include "chat.h"

#define	MAX_BUF		256

int			Sockfd;
pthread_t	Tid1, Tid2;

void
SendMsg(void* dummy){
	char msg[MAX_BUF];
	
	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL))  {
		perror("pthread_setcancelstate");
		exit(1);
	}
	if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL))  {
		perror("pthread_setcanceltype");
		exit(1);
	}

	while(1){
		fgets(msg, MAX_BUF, stdin);
		if( send(Sockfd, msg, strlen(msg)+1, 0) <0){
			perror("send");
			exit(1);
		}
	}
}

void
ReceiveMsg(void* dummy){
	char	msg[MAX_BUF];
	int		n;

	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL))  {
		perror("pthread_setcancelstate");
		exit(1);
	}
	if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL))  {
		perror("pthread_setcanceltype");
		exit(1);
	}

	while(1){
		if((n = recv(Sockfd, msg, MAX_BUF, 0))<0)	{
			perror("recv");
			exit(1);
		}
		if(n==0){
			fprintf(stderr, "Server terminated....\n");

			close(Sockfd);
			if( pthread_cancel(Tid1) <0){
				perror("pthread_cancel");
				exit(1);
			}
			pthread_exit(NULL);
		}
		
		printf("%s", msg);
	}
}

void
ChatClient(void)
{
	char	buf[MAX_BUF];
	int		count, n;

	printf("Enter ID: ");
	fflush(stdout);
	fgets(buf, MAX_BUF, stdin);

	//stchr : find a character in string 
	*strchr(buf, '\n') = '\0';

	//SEND
	if (send(Sockfd, buf, strlen(buf)+1, 0) < 0)  {
		perror("send");
		exit(1);
	}
	printf("Press ^C to exit\n");

	if(pthread_create(&Tid1, NULL, (void *)SendMsg, (void *)NULL) <0){
		perror("pthread_create");
		exit(1);
	}
	
	if(pthread_create(&Tid2, NULL, (void *)ReceiveMsg, (void *)NULL) <0) {
		perror("pthread_create");
		exit(1);
	}

	if( pthread_join(Tid1, NULL)){
		perror("pthread_join");
		exit(1);
	}

	if( pthread_join(Tid2, NULL)){
		perror("pthread_join");
		exit(1);
	}

	printf("\nChat client terminated.....\n");
}
	

void
CloseClient(int signo)
{
	//close the Sockfd
	close(Sockfd);

	if( pthread_cancel(Tid1) ) {
		perror("pthread_cancel");
		exit(1);
	}
	
	if( pthread_cancel(Tid2) ) {
		perror("pthread_cancel");
		exit(1);
	}

	if( pthread_join(Tid1, NULL)){
		perror("pthread_join");
		exit(1);
	}

	if( pthread_join(Tid2, NULL)){
		perror("pthread_join");
		exit(1);
	}

	printf("\nChat client terminated.....\n");

	exit(0);
}

void
main(int argc, char *argv[])
{
	struct sockaddr_in	servAddr;
	struct hostent		*hp;
	
	//check the argc 
	if (argc != 2)  {
		fprintf(stderr, "Usage: %s ServerIPaddress\n", argv[0]);
		exit(1);
	}

	//SOCKET
	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_port = htons(SERV_TCP_PORT);

	if (isdigit(argv[1][0]))  {
		servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	}
	else  {
		if ((hp = gethostbyname(argv[1])) == NULL)  {
			fprintf(stderr, "Unknown host: %s\n", argv[1]);
			exit(1);
		}
		memcpy(&servAddr.sin_addr, hp->h_addr, hp->h_length);
	}

	//CONNET
	if (connect(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("connect");
		exit(1);
	}
	
	//Register a signal handler
	signal(SIGINT, CloseClient);

	ChatClient();
}
