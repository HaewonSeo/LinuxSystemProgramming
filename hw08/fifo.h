#define	MAX_FIFO_NAME	32

//fifo for server use
#define	SERV_FIFO	"./.fifo"

// Message structure
typedef struct  {
	char	returnFifo[MAX_FIFO_NAME];// fifo for client use
	char	data[128];
}
	MsgType;
