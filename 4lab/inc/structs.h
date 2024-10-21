#ifndef STRUCTS_H
#define STRUCTS_H

#include "definitions.h"


typedef struct
{
    char data[MAX_LEN_STACK];
    int top;    
} static_array_stack_t;


typedef struct
{
    char *data;
    int top;
    int capacity;
} dynamic_array_stack_t;

typedef struct
{
    char data;
    struct list_stack_t *next;
} list_stack_t;


typedef enum { STATIC_ARRAY, DYNAMIC_ARRAY, LIST } stack_type_t;



#endif