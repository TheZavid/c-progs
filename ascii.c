#include <stdio.h>
#include <ctype.h>

int
main(void)
{
	int i = 1;
	while(i <= 128){
		if(isprint(i) != 0) printf("%02x %c\t", i - 1, i - 1);
		if(isprint(i) == 0) printf("%02x NP\t", i - 1);
		if(i % 8 == 0) printf("\n");
		i++;
	}
}
