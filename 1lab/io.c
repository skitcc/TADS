#include "io.h"

int input(char *my_int, char *my_double)
{
    if (fgets(my_int, MAX_LEN_INT + 1, stdin) == NULL)
        return 1;

    
    
    if (fgets(my_double, MAX_LEN_DOUBLE + 1, stdin) == NULL)
        return 2;

    printf("strlwen my int : %zu\n", strlen(my_int));
    printf("strlwen my double : %zu\n", strlen(my_double));
    my_int[strlen(my_int) - 1] = '\0';
    my_double[strlen(my_double) - 1] = '\0';

    return 0;
    
}