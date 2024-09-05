#include "io.h"

int input(char *my_int, char *my_double)
{
    if (fgets(my_int, MAX_LEN_INT + 1, stdin) == NULL)
        return 1;

    if (fgets(my_double, MAX_LEN_DOUBLE + 1, stdin) == NULL)
        return 2;

    return 0;
    
}