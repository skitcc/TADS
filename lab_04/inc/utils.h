#ifndef UTILS_H
#define UTILS_H

#include "definitions.h"
#include "structs.h"
#include "stack_operations.h"

#include <stdio.h>
#include <stdlib.h>


void init_dynamic_array_stack(dynamic_array_stack_t *s);
void init_static_array_stack(static_array_stack_t *s);
size_t calculate_list_memory(const list_stack_t *stack);

#endif