#ifndef STRUCT_H
#define STRUCT_H
#include "definitions.h"

typedef struct
{
    char num_sign;
    char mantissa[MAX_LEN_MANTISSA + 1];
    char exp_sign;
    char order[MAX_LEN_ORDER + 1];
} double_data;


typedef struct
{
    char num_sign;
    char int_value[MAX_LEN_INT + 1];
} int_data;


typedef struct
{
    char num_sign;
    char mantissa[MAX_LEN_MANTISS_RESULT_I + 1];
    char exp_sign;
    char order[MAX_LEN_ORDER + 1];
} result_data;


#endif