#include <stdio.h>

#define CHAR_TO_DELETE 'o'

void
delete(char c)
{       
        char cur_c;
        while ((cur_c = getchar()) != EOF) {
                if (cur_c != c)
                        putchar(cur_c);
        }
}

void 
squeze(char c)
{
        char cur_c;
        while ((cur_c = getchar()) != EOF) {
                putchar(cur_c);
                if (cur_c == c) {
                        while ((cur_c = getchar()) == c) continue;
                        putchar(cur_c);
                }
        }
}

int
main(void)
{
        squeze(CHAR_TO_DELETE);
}