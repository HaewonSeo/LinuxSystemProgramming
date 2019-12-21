#define	MY_ID			

#define	SERV_TCP_PORT	(7000 + 24)
#define	SERV_HOST_ADDR	"163.180.140.215"


typedef struct  {
	int		num;
	char	id[10];
	char	data[128];
}
	MsgType;
