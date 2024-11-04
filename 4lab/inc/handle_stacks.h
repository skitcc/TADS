#ifndef HANDLE_STACKS_H
#define HANDLE_STACKS_H

#include "structs.h"
#include "definitions.h"
#include "stack_operations.h"
#include "print.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void initialize_stacks(static_array_stack_t *st_arr_stack, dynamic_array_stack_t *dn_arr_stack, list_stack_t **list_stack);
void fill_stack_from_expression(const char *expr, void *stack, stack_type_t type);
void handle_static_stack();
void handle_dynamic_stack();
void handle_list_stack();





#endif