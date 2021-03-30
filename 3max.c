#include <stdio.h>

int
max(int i, int j, int k)
{
        return ( i > j ? ( i > k ? i : k ) : ( j > k ? j : k ) );
}

int
main(void)
{
        
}