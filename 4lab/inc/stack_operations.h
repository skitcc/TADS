#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H


#include "definitions.h"
#include "structs.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void init_static_array_stack(static_array_stack_t *s);
void init_dynamic_array_stack(dynamic_array_stack_t *s);
list_stack_t *init_list_stack();
int push(void *stack, stack_type_t type, char value);
char pop(void *stack, stack_type_t type);
void print_stack(void *stack, stack_type_t type);
bool check_brackets(const char *expr, void *stack, stack_type_t type);
bool is_empty(void *stack, stack_type_t type);
void free_dynamic_array_stack(dynamic_array_stack_t *stack);
void free_list_stack(list_stack_t **stack);


#endif