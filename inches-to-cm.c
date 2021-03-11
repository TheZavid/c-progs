#include <stdio.h>
#include <string.h>

int
main(void)
{
	int i = 1;
	float cm;

	printf("Inches\tCentimeteres\n");
	while (i < 10) {
		cm = i * 2.54;
		printf("%d\t%6.2f\n", i, cm);
		++i;
	}
}
