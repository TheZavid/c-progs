#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int
get_y(int x, int radius)
{
    return (int) sqrt(radius * radius - x * x) - 1;
}

void
graph_cirle(char **cirle, int radius)
{
    for(int x = -radius; x <= radius; x++) {
        int y = get_y(x, radius);
        cirle[radius - y][x+radius] = '*';
        cirle[radius + y][x+radius] = '*';
    }
    for(int y = 0; y < 2*radius; y++)
        printf("%s\n", cirle[y]);
}


int
main (int argc, char* argv[])
{
    int radius = 3;
    if (argc > 1)
        radius = atoi(argv[1]);
    char** cirle = (char**) malloc(radius*2 * sizeof(char*));
    for (int i = 0; i < radius*2; i++) {
        cirle[i] = (char*) malloc((radius*2 + 1) * sizeof(char));
        memset(cirle[i], ' ', radius*2 * sizeof(char));
        cirle[i][radius*2 + 1] = '\0';
    }
    graph_cirle(cirle, radius);
}