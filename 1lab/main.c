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
    double_data whole_double_num; 
    int_data whole_int_num;
    result_data whole_result_num;


    short rc = input(&whole_int_num, &whole_double_num);
    if (rc)
        return rc;


    // short ic = check_int(my_int, &whole_int_num);

    // if (ic)
    //     return ic;

    short rm = mantissa_check(&whole_double_num);
    if (rm)
        return rm;

    

    printf("double_num : %c%sE%c%s\n", whole_double_num.num_sign, whole_double_num.mantissa, whole_double_num.exp_sign, whole_double_num.order);
    printf("int_num : %c%s\n", whole_int_num.num_sign, whole_int_num.int_value);

    matrix_generator(&whole_double_num, &whole_int_num, &whole_result_num);



}