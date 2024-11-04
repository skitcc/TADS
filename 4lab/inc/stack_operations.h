#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H


#include "definitions.h"
#include "structs.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


list_stack_t *init_list_stack();
int push(void *stack, stack_type_t type, char value);
char pop(void *stack, stack_type_t type, removed_addresses_tracker_t *tracker);
void print_stack(void *stack, stack_type_t type);
bool check_brackets(void *stack, stack_type_t type, const char *expr);
bool is_empty(void *stack, stack_type_t type);
void free_dynamic_array_stack(dynamic_array_stack_t *stack);
void free_list_stack(list_stack_t **stack);
int push_list(list_stack_t **stack, char value);
char pop_list(list_stack_t **stack, removed_addresses_tracker_t *tracker);
bool check_brackets_list(const char *expr);

#endif