#include "io.h"
#include "definitions.h"
#include "mantiss_format.h"

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    char my_int[MAX_LEN_INT + 1];
    char my_double[MAX_LEN_DOUBLE + 1];

    char format_double[MAX_LEN_DOUBLE + 1];


    short rc = input(my_int, my_double);
    if (rc)
        return rc;

    short rm = check_mantiss(my_double, format_double);
    short ic = check_int(my_int);

    if (ic)
        return ic;

    if (rm)
        return rm;

    printf("%s\n", format_double);





}