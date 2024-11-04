#ifndef UTILS_H
#define UTILS_H

#include "definitions.h"
#include "structs.h"
#include "stack_operations.h"

#include <stdio.h>
#include <stdlib.h>



void initialize_stacks(static_array_stack_t *st_arr_stack, dynamic_array_stack_t *dn_arr_stack, list_stack_t **list_stack);
void fill_stack_from_expression(const char *expr, void *stack, stack_type_t type);
void fill_list(const char *expr, list_stack_t **stack);


#endif