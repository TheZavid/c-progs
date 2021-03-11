#include <stdio.h>
#include <string.h>

int
main(void)
{
	printf("\x1B[5mEll\tInches\tCentimeteres\x1B[0m\n");
	int i = 0;
	while(i < 30){
		printf("\x1B[4m\x1B[5m \x1B[0m");
		i++;
	}
	printf("\n");
	i = 1;
	while(i <= 30){
		printf("\x1B[31m%d\t",i);
		printf("\x1B[32m%d\t", i*45);
		printf("\x1B[33m%.2f\x1B[0m\n", i *114.3);
		if( i%10 == 0) {
			int j = 0;
			while(j < 30){
				printf("\x1B[4m\x1B[5m \x1B[0m");
				j++;
			}
			printf("\n");
		}
		i++;
	}
} 
