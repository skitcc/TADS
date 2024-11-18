#ifndef VIZUALIZE_TREE_H
#define VIZUALIZE_TREE_H


#include <stdio.h>
#include <stdlib.h>


#include "tree_operations.h"
#include "definitions.h"


void export_to_dot(node_t *root, const char *filename);

#endif