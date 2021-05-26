#include <stdio.h>
#include "animals.h"
#include "maxlegs_util.c"

int
main()
{
    printf("%s\n", maxlegs(animals, sizeof(animals) / sizeof(animals[0]))->name);
}