#include "io.h"
#include "definitions.h"
#include "parse_double.h"
#include "struct.h"
#include "parse_int.h"
#include "multiply.h"
#include "print_result.h"

#include <stdio.h>
#include <stdlib.h>



int main(void)
{
    double_data whole_double_num; 
    int_data whole_int_num;
    result_data whole_result_num;

    char int_num[MAX_LEN_INT_I];
    char double_num[MAX_LEN_DOUBLE_I];

    // Ввод данных
    short rc = input(int_num, double_num);
    if (rc)
        return rc;

    short ic = check_int(int_num, &whole_int_num);
    printf("int_len : %zu\n", whole_int_num.len);
    if (ic)
        return ic;

    short rm = mantissa_check(double_num, &whole_double_num);
    if (rm)
        return rm;

    // Выполнение умножения
    multiply(&whole_double_num, &whole_int_num, &whole_result_num);
    print_result(&whole_result_num);
    

    return 0;
}
