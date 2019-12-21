#define	MY_ID			24

#define	SERV_TCP_PORT	(7000 + MY_ID)
#define	SERV_HOST_ADDR	"127.18.0.1"

#define	MSG_REQUEST		1
#define	MSG_REPLY		2


typedef struct  {
	char	filename[20];
	long	sec;
	long	usec;
}
	MsgType;
