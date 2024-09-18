#include "io.h"
#include "definitions.h"
#include "parse_double.h"
#include "struct.h"
#include "parse_int.h"
#include "multiply.h"
#include "distribute.h"

#include <locale.h>

#include <stdio.h>
#include <stdlib.h>



int main(void)
{
    setlocale(LC_ALL, "C");
    double_data whole_double_num; 
    int_data whole_int_num;
    result_data whole_result_num;


    char int_num[MAX_LEN_INT_I];
    char double_num[MAX_LEN_DOUBLE_I];

    char new_double[MAX_LEN_DOUBLE];
    char new_int[MAX_LEN_INT_I];


    short rc = input(int_num, double_num);
    if (rc)
        return rc;


    short ic = check_int(int_num, new_int);

    if (ic)
        return ic;

    short rm = mantissa_check(double_num, new_double);

    // printf("new_double : %s\n", new_double);
    printf("rm = %d\n", rm);
    if (rm)
        return rm;


    if (distribute_to_double_data(&whole_double_num, new_double, strlen(new_double)))
        return 1;
    distribute_to_int_data(&whole_int_num, new_int, strlen(new_int));


    printf("Приведенное к стандарту целое число : %c%s\n", whole_int_num.num_sign, whole_int_num.int_value);

    printf("Приведенное к стандарту вещественное число : %c%sE%c%s\n", whole_double_num.num_sign, whole_double_num.mantissa, whole_double_num.exp_sign, whole_double_num.order);


    if (matrix_generator(&whole_double_num, &whole_int_num, &whole_result_num)) 
        return 4;



}