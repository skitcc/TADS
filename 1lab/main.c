#include "io.h"
#include "definitions.h"

#include <stdio.h>




int check_mantiss(char *my_double)
{
    if (my_double[0] != '+' || my_double[0] != '-')
        return WRONG_SIGN;

    size_t i_m = 0, i_n = 0;
    short m = 0, n = 0;

    while (my_double[i_m] != '.')
        m++

    while (my_double[i)])
}


int main(void)
{
    char my_int[MAX_LEN_INT + 1];
    char my_double[MAX_LEN_DOUBLE + 1];


    short rc = input(my_int, my_double);
    if (rc)
        return rc;






}