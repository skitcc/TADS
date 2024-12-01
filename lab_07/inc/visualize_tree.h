#ifndef VIZUALIZE_TREE_H
#define VIZUALIZE_TREE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree_operations.h"
#include "definitions.h"


void export_to_dot(void *head, const char *filename, bool is_bst);
bool has_cycle(void *head);


#endif