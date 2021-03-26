#include <stdio.h>

int
main(void)
{
	unsigned int c, words = 0, is_word = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t'){
			words += is_word;
			is_word = 0;
			continue;
		}
		is_word = 1;
	}

	printf("%d", words);
}
