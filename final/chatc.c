#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "chat.h"

#define	MAX_BUF		256

int		Sockfd;
char	id[10];

void
ChatClient(void)
{
	char	buf[MAX_BUF];
	int		count, n;
	fd_set	fdset;

	printf("Press ^C to exit\n");

	fgets(buf, MAX_BUF, stdin);
	*strchr(buf, '\n') = '\0';

	if (send(Sockfd, id, 10, 0) < 0)  {
		perror("send");
		exit(1);
	}
	if (send(Sockfd, buf, strlen(buf)+1, 0) < 0)  {
		perror("send");
		exit(1);
	}

	while (1)  {
		FD_ZERO(&fdset);
		FD_SET(Sockfd, &fdset);
		FD_SET(STDIN_FILENO, &fdset);

		if ((count = select(10, &fdset, (fd_set *)NULL, (fd_set *)NULL,
			(struct timeval *)NULL)) < 0)  {
			perror("select");
			exit(1);
		}
		while (count--)  {
			if (FD_ISSET(Sockfd, &fdset))  {
				if ((n = recv(Sockfd, buf, MAX_BUF, 0)) < 0)  {
					perror("recv");
					exit(1);
				}
				if (n == 0)  {
					fprintf(stderr, "Server terminated.....\n");
					close(Sockfd);
					exit(1);
				}
				printf("%s", buf);
			}
			else if (FD_ISSET(STDIN_FILENO, &fdset))  {
				fgets(buf, MAX_BUF, stdin);
				if ((n = send(Sockfd, buf, strlen(buf)+1, 0)) < 0)  {
					perror("send");
					exit(1);
				}
			}
		}
	}
}
	

void
CloseClient(int signo)
{
	close(Sockfd);
	printf("\nChat client terminated.....\n");

	exit(0);
}


main(int argc, char *argv[])
{
	struct sockaddr_in	servAddr;
	struct hostent		*hp;

	if (argc != 3)  {
		fprintf(stderr, "Usage: %s ServerIPaddress ID\n", argv[0]);
		exit(1);
	}

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

	if (connect(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("connect");
		exit(1);
	}
	
	strcpy(id, argv[2]);

	signal(SIGINT, CloseClient);

	ChatClient();
}
