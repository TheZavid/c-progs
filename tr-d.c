#include <stdio.h>

void
delete(char c)
{       
        char cur_c;
        while ((cur_c = getchar()) != EOF) {
                if (cur_c != c)
                        putchar(cur_c);
        }
}

int
main(void)
{
        delete('d');
}