#include "animal-struct.h"

size_t
get_legs(struct animal *a)
{
    return a->legs;
}

struct animal *
maxlegs(struct animal *a, size_t size)
{
    struct animal *copy = a, *max = a;
    for (size_t i = 0; i < size; i++) {
        if(get_legs(copy) > get_legs(max))
            max = copy;
        copy++;
    }
    return max;
}