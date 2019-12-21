// for checking SIGBUS signal
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void SigBusHandler(int signo){
	printf("odd pointer error");
	fflush(stdout);
	exit(0);
}

void main(){
	
	signal(SIGBUS,SigBusHandler);

	char *p;
	int a,b;
	
	p=&b;
	p++;

	a = (int *)p;
}
