#include <stdio.h>
#include <string.h>

int
main(void)
{
	int F = 0;
	float C;
	float con = 5.0/9.0;

	printf("Fahrenheit\tCentigrade\n");
	while (F < 100){
		C = (F - 32) * con;
		printf("%d\t%6.2f\n", F, C);
		++F;
	}
}
