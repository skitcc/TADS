#ifndef STRUCT_H
#define STRUCT_H
#include "definitions.h"
#include <stddef.h>

typedef struct
{
    int num_sign;
    int mantissa[MAX_LEN_MANTISSA + 1];
    int exp_sign;
    int exp;
    size_t len;
} double_data;


typedef struct
{
    int num_sign;
    int int_value[MAX_LEN_INT_I + 1];
    size_t len;
} int_data;

typedef struct
{
    int num_sign;
    int mantissa[MAX_LEN_MANTISS_RESULT_I + 1];
    int exp_sign;
    int exp;
    size_t len;
} result_data;

#endif
