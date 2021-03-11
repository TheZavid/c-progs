#include <stdio.h>

#define CONVERT 32

int
main(void)
{
	char c;

	while(1){
		c = getchar();
		if( c == EOF) break;
		
		if( c >= 65 && c <= 90){
			c += CONVERT;
		} else if(c >= 97 && c <= 122){
			c -= CONVERT;
		}

		putchar(c);

	}
}
