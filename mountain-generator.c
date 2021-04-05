#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char directions[3]="/_\\"; // possible direction mountain can go

int
choose_dir(size_t h, size_t height)
{       
        int dir;
        while (1) {
                // gives us integer value [-1,1] which helps to update height latter on
                dir = rand() % 3 - 1;
                // if we hit the bounds generate new
                if ((h == 0 && dir == -1) || (h == height - 1 && dir == 1))
                        continue;
                break;
        }
        return dir;
}


void
print_mountain(size_t height, size_t width, char mt[height][width])
{
        for (size_t h = 0; h < height; h++){
                for (size_t w = 0; w < width; w++) {
                        putchar(mt[h][w]);
                }
                putchar('\n');
        }
}

void
generate_mountain(size_t height, size_t width)
{
        char mountain[height][width];
        // set all elements in array to ' '
        memset(mountain, ' ', sizeof (mountain));
        // random number seed for rand()
        srand(time(NULL));
        size_t h = height - 1;
        int dir = 0;
        for (size_t w = 0; w < width; w++) {
                dir = choose_dir(h, height);
                if (dir == 1) // if we go down then go down now
                        h += dir;
                mountain[h][w] = directions[dir + 1];
                if (dir == -1) // if we go up place the next character up but dont go up yourself
                        h += dir;
        }
        print_mountain(height, width, mountain);
}


int
main(int argc, char *argv[])
{
        size_t height = 30, width = 80;

        if (argc > 1)
                height = atoi(argv[1]);
                
        if (argc > 2)
                width = atoi(argv[2]);
        generate_mountain(height, width);
}