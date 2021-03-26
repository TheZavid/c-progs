#include <stdio.h>

int
myisdigit(char c)
{
        if (c >= '0' && c <= '9') {
                return 1;
        } else
                return 0;
}

int
myisspace(char c)
{
        if (c == ' ' || c == '\t' || c == '\n') {
                return 1;
        } else
                return 0;
}


int
main(void)
{
        char c;
        int occurence[3] = {0, 0, 0};

        while ((c = getchar()) != EOF) {
                if (myisdigit(c))
                        occurence[0]++;
                else if (myisspace(c))
                        occurence[1]++;
                else
                        occurence[2]++;
        }
        printf("Number of digits: %d\n", occurence[0]);
        printf("Number of spaces: %d\n", occurence[1]);
        printf("Number of other: %d\n", occurence[2]);
}