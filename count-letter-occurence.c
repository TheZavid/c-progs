#include <stdio.h>

#define CONVERT 32

int occurence[26];

int
mytolower(char c)
{       
        return c + CONVERT;
}

void
evaluate(char c)
{
        if (c >= 'A' && c <= 'Z')
                occurence[mytolower(c) - 'a']++;
        else if (c >= 'a' && c <= 'z')
                occurence[c - 'a']++;
}

void
putstars(int n)
{
        for (int i = 0; i < n; i++)
                putchar('*');
}

void
printout()
{
        for (int i = 0; i < 26; i++) {
                printf("%c: ", i + 'a');
                putstars(occurence[i]);
                printf("\n");
        }
}

int
main(void)
{
        char c;
        while ((c = getchar()) != EOF) {
                evaluate(c);
        }
        printout();
}