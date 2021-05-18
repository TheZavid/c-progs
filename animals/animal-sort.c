#include <stdio.h> //printf
#include <stdlib.h> //qsort
#include <string.h> //strcmp
#include <err.h> //errx
#include "animal-struct.h"
#include "animals.h"

int
name_compar(const void *ta, const void *tb)
{
    struct animal *a = (struct animal *) ta;
    struct animal *b = (struct animal *) tb;
    return strcmp(a->name, b->name);
}

int
legs_compar(const void *ta, const void *tb)
{
    struct animal *a = (struct animal *) ta;
    struct animal *b = (struct animal *) tb;
    if (a->legs > b->legs)
        return 1;
    else if (a->legs < b->legs)
        return -1;
    else
        return 0;
}

void
print_animal(struct animal *a)
{
    printf("Name: %s\n\tLegs: %zu\n", a->name, a->legs);
}

int
main(int argc, char *argv[])
{
    if (argc < 2)
        errx(1, "wrong number of arguments");
    int (*compar)(const void *, const void *);
    switch (atoi(argv[1])) {
    case 0:
        compar = name_compar;
        break;
    case 1:
        compar = legs_compar;
        break;
    default:
        errx(2, "wrong arguments");
        break;
    }

    qsort(animals, sizeof(animals) / sizeof(animals[0]), sizeof(animals[0]),
          compar);
    for(size_t i = 0; i < sizeof(animals) / sizeof(animals[0]); i++)
        print_animal(&animals[i]);
}