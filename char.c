#include <stdio.h>

int
main(void)
{
	char arr[] = {'h', 'u', 'i'};
	int i = 0;
	while(i < sizeof(arr)/sizeof(arr[0])){
		printf("%c\n", arr[i]);
		i++;
	}
}
