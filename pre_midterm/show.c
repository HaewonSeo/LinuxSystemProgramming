#include <stdio.h>

void
main()
{

	int i;
	int j;

	for(j=9; j>0;j--){
		for(i=1;i<=j;i++){
			printf("%d ",i);
		}
		printf("\n");
	}
}
