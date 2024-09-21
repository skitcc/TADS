#ifndef STRUCT_H
#define STRUCT_H
#include "definitions.h"

typedef struct
{
    int num_sign;
    int mantissa[MAX_LEN_MANTISSA + 1];
    int exp_sign;
    int order[MAX_LEN_ORDER_I + 1];
} double_data;


typedef struct
{
    int num_sign;
    int int_value[MAX_LEN_INT_I + 1];
} int_data;


typedef struct
{
    int num_sign;
    int mantissa[MAX_LEN_MANTISS_RESULT_I + 1];
    int exp_sign;
    int order[MAX_LEN_ORDER_I + 1];
} result_data;


#endif