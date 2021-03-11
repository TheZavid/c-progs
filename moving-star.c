#include <stdio.h>
#include <string.h>
#include <poll.h>

int
main(void)
{
	int indent = 0;
	int boundary = 50;
	int iterator = -1;

	while(1){
		printf("\r|");
		if (indent == boundary || indent == 0)
			iterator *= -1;
		printf("%*s", indent, "*");
		printf("%*s", boundary - indent + 1, "|");
		poll(NULL, 0, 50);
		fflush(stdout);
		indent += iterator;
	}
}
