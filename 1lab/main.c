#include "io.h"
#include "definitions.h"
#include "parse_double.h"
#include "struct.h"
#include "parse_int.h"
#include "multiply.h"

#include <stdio.h>
#include <stdlib.h>



int main(void)
{
    char my_int[MAX_LEN_INT + 1];
    char my_double[MAX_LEN_DOUBLE + 1];
    double_data whole_double_num; 
    int_data whole_int_num;
    result_data whole_result_num;


    short rc = input(my_int, my_double);
    if (rc)
        return rc;


    short ic = check_int(my_int, &whole_int_num);

    if (ic)
        return ic;

    short rm = check_mantiss(my_double, &whole_double_num);

    if (rm)
        return rm;

    

    printf("%c %s %c %s\n", whole_double_num.num_sign, whole_double_num.mantissa, whole_double_num.exp_sign, whole_double_num.order);
    printf("%c %s\n", whole_int_num.num_sign, whole_int_num.int_value);

    matrix_generator(&whole_double_num, &whole_int_num, &whole_result_num);



}